#include "Eye/Lexer/Lexer.h"
#include "Eye/Util/Logger.h"

namespace EYE
{
	LexerResult Lexer::Tokenize(EyeInstance* eyeInstance)
	{
		m_EyeInstance = eyeInstance;
		m_Position.FileName = m_EyeInstance->InFilePath;

		Token token = NextToken();
		while (token)
		{
			m_Tokens.push_back(token);
			token = NextToken();
		}

		return LexerResult::Successful;
	}

	std::vector<Token> Lexer::GetTokens() const
	{
		return m_Tokens;
	}

	void Lexer::DebugPrintTokens() const
	{
		for (const auto& token : m_Tokens)
			std::cout << token << std::endl;
	}

	Token Lexer::NextToken()
	{
		Token token;

		char c = PeekChar();
		switch (c)
		{
			// Whitespace
		case ' ':
		case '\t':
			token = HandleWhitespace();
			break;

			// Newline
		case '\n':
			token = HandleNewline();
			break;

			// Numbers
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			token = MakeNumberToken();
			break;

			// Numbers other Base Types
		case 'x':
		case 'b':
			token = MakeNumberBaseToken();
			break;

			// Strings
		case '"':
			token = MakeStringToken('"', '"');
			break;

			// Character
		case '\'':
			token = MakeCharacterToken();
			break;

			// Operators
		case '+':
		case '-':
		case '*':
		case '%':
		case '=':
		case '<':
		case '>':
		case '!':
		case '&':
		case '|':
		case '^':
		case '~':
		case '[':
		case '(':
		case '?':
		case ',':
			token = MakeOperatorToken();
			break;

			// Symbols
		case '{':
		case '}':
		case ':':
		case ';':
		case '\\':
		case ')':
		case ']':
			token = MakeSymbolToken();
			break;

		case EOF:
			break;

		default:
			EYE_LOG_CRITICAL("Lexer->Unexpected Token : {}\n on line {}, col {} in file {}", c, m_Position.Line, m_Position.Col, m_Position.FileName);
			break;
		}

		return token;
	}

	Token Lexer::HandleWhitespace()
	{
		NextChar();
		return NextToken();
	}

	Token Lexer::HandleNewline()
	{
		NextChar();
		Token token;
		token.Type = TokenType::Newline;
		token.Position = m_Position;
		return token;
	}

	Token Lexer::MakeNumberToken()
	{
		std::string numbers;
		for (char c = PeekChar(); c >= '0' && c <= '9'; c = PeekChar())
		{
			numbers.push_back(c);
			NextChar();
		}

		Token token;
		token.Type = TokenType::Number;
		token.Position = m_Position;
		token.Number = std::atoi(numbers.c_str());
		return token;
	}

	Token Lexer::MakeNumberBaseToken()
	{
		if (m_Tokens.empty() || !(m_Tokens.back().Type == TokenType::Number && m_Tokens.back().Number == 0))
			return {}; // Identifier...

		Token lastToken = m_Tokens.back();
		m_Tokens.pop_back();

		char baseType = PeekChar();
		if (baseType == 'x')
			return MakeHexNumberToken();
		else if (baseType == 'b')
			return MakeBinaryNumberToken();

		return {};
	}

	Token Lexer::MakeHexNumberToken()
	{
		NextChar();

		std::string hexStr{};
		for (char c = PeekChar(); IsValidHexNumber(c); c = PeekChar())
		{
			hexStr += c;
			NextChar();
		}

		Token token;
		token.Type = TokenType::Number;
		token.Position = m_Position;
		token.Number = std::strtol(hexStr.c_str(), 0, 16);
		return token;
	}

	Token Lexer::MakeBinaryNumberToken()
	{
		NextChar();
	
		std::string binaryStr;
		for (char c = PeekChar(); c >= '0' && c <= '9'; c = PeekChar())
		{
			binaryStr.push_back(c);
			NextChar();
		}

		if (!IsValidBinaryNumber(binaryStr))
			EYE_LOG_CRITICAL("Lexer->Bad Binary Number Format : {}\n on line {}, col {} in file {}", binaryStr, m_Position.Line, m_Position.Col, m_Position.FileName);

		Token token;
		token.Type = TokenType::Number;
		token.Position = m_Position;
		token.Number = std::strtol(binaryStr.c_str(), 0, 2);
		return token;
	}

	Token Lexer::MakeStringToken(char sdelim, char edelim)
	{
		if(NextChar() != sdelim)
			EYE_LOG_CRITICAL("Lexer->Bad String Delimiter: {}\n on line {}, col {} in file {}", sdelim, m_Position.Line, m_Position.Col, m_Position.FileName);

		std::string str;
		for (char c = NextChar(); c != edelim && c != EOF; c = NextChar())
		{
			if (c == '\\')
				continue;
			str.push_back(c);
		}

		Token token;
		token.Type = TokenType::String;
		token.Position = m_Position;
		token.String = (new std::string(str))->c_str();
		return token;
	}

	Token Lexer::MakeCharacterToken()
	{
		NextChar();

		bool escapedChar = false;
		char c = NextChar();
		if (c == '\\')
		{
			c = NextChar();
			c = CharToEscapedChar(c);
			escapedChar = true;
		}
		
		if (NextChar() != '\'')
			EYE_LOG_CRITICAL("Lexer Bad Character Quote Format : {}\n on line {}, col {} in file {}", c, m_Position.Line, m_Position.Col, m_Position.FileName);

		Token token;
		token.Type = escapedChar ? TokenType::EscapeCharacter : TokenType::Number;
		token.Position = m_Position;
		token.Char = c;
		return token;
	}

	Token Lexer::MakeOperatorToken()
	{
		bool singleOperator = true;

		char op = NextChar();
		std::string opStr{ op };

		if (!IsSinglyOperator(op))
		{
			// Stackable Operator: i.e ++
			op = PeekChar();
			if (IsOperator(op))
			{
				opStr += op;
				singleOperator = false;
				NextChar();
			}
		}

		// PutBack All Except First One
		if (!singleOperator && !IsValidOperator(opStr))
			for (size_t i = opStr.size() - 1; i >= 1; i--)
				PutBack(opStr[i]);

		if (singleOperator && !IsValidOperator(opStr))
			EYE_LOG_CRITICAL("Lexer->Invalid Operator: {}\n on line {}, col {} in file {}", opStr, m_Position.Line, m_Position.Col, m_Position.FileName);

		Token token;
		token.Type = TokenType::Operator;
		token.Position = m_Position;
		token.String = (new std::string(opStr))->c_str();
		return token;		
	}

	Token Lexer::MakeSymbolToken()
	{
		char c = NextChar();
		Token token;
		token.Type = TokenType::Symbol;
		token.Position = m_Position;
		token.Char = c;
		return token;
	}

	bool Lexer::IsOperator(char op) const
	{
		return (op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || 
			op == '=' || op == '<' || op == '>' || op == '!' || 
			op == '&' || op == '|' || op == '^' || op == '~' ||
			op == '[' || op == '(' || op == '?' || op == ',');
	}

	bool Lexer::IsSinglyOperator(char op) const
	{
		return (op == ',' || op == '(' || op == '[' || op == '?' || op == '*');
	}

	bool Lexer::IsValidOperator(const std::string& op) const
	{
		return (op == "+" || op == "-" || op == "*" || op == "/" || op == "%" || op == "++" || op == "--" ||
			op == "=" || op == "+=" || op == "-=" || op == "*=" || op == "/=" || op == "%=" || op == "&=" || op == "|=" || op == "^=" || op == ">>=" || op == "<<=" ||
			op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=" ||
			op == "&&" || op == "||" || op == "!" ||
			op == "&" || op == "|" || op == "^" || op == "<<" || op == ">>" || op == "~" ||
			op == "(" || op == "[" || op == "?" || op == ",");
	}

	bool Lexer::IsValidHexNumber(char num) const
	{
		num = std::tolower(num);
		return ((num >= '0' && num <= '9') || (num >= 'a' && num <= 'f'));
	}

	bool Lexer::IsValidBinaryNumber(const std::string& num) const
	{
		for (const auto& n : num)
			if (n != '0' && n != '1')
				return false;
		return true;
	}

	char Lexer::CharToEscapedChar(char c) const
	{
		char ch = 0;
		switch (c)
		{
		case 'n':
			ch = '\n';
			break;
		case 't':
			ch = '\t';
			break;
		case '\\':
			ch = '\\';
			break;
		case '\'':
			ch = '\'';
			break;
		}
		return ch;
	}

	char Lexer::NextChar()
	{
		char c = m_EyeInstance->InFileStream.get();
		m_Position.Col++;
		if (c == '\n')
		{
			m_Position.Line++;
			m_Position.Col = 1;
		}
		return c;
	}

	char Lexer::PeekChar() const
	{
		return m_EyeInstance->InFileStream.peek();
	}

	void Lexer::PutBack(char c)
	{
		m_EyeInstance->InFileStream.putback(c);
	}
}
