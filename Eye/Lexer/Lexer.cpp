#include "Eye/Lexer/Lexer.h"
#include "Eye/Utility/FileIO.h"
#include "Eye/Utility//Logger.h"
#include "Eye/Error/Exceptions/UnexpectedTokenException.h"

namespace Eye
{
	std::expected<std::vector<std::unique_ptr<Token>>, Error::Error> Lexer::Tokenize(const EyeSource& source)
	{
		m_Source = source;

		if (m_Source.Type == EyeSourceType::File)
			m_BufferStream = std::istringstream(FileIO::ReadFileContent(m_Source.Source));
		else if (m_Source.Type == EyeSourceType::String)
			m_BufferStream = std::istringstream(m_Source.Source);

		try
		{
			std::unique_ptr<Token> token = NextToken();
			while (token)
			{
				m_Tokens.push_back(token);
				token = NextToken();
			}
		}
		catch (const Error::Exceptions::EyeException& ex)
		{
			return std::unexpected(ex.GetError());
		}
		catch (...)
		{
			EYE_LOG_CRITICAL("EYELexer->Tokenize Unknown Exception!");
		}

		m_Tokens.push_back(MakeEOFToken());
		return std::move(m_Tokens);
	}

	std::unique_ptr<Token> Lexer::NextToken()
	{
		std::unique_ptr<Token> token;

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
		case '.':
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

			// Slash Operator
		case '/':
			token = HandleSlashOperator();
			break;

		case EOF:
			break;

		default:
			token = MakeSpecialToken();
			if (!token)
				throw Error::Exceptions::UnexpectedTokenException(std::string{ c }, Error::ErrorType::LexerUnexpectedToken, m_Source);
			break;
		}

		return token;
	}

	std::unique_ptr<Token> Lexer::HandleWhitespace()
	{
		NextChar();
		return NextToken();
	}

	std::unique_ptr<Token> Lexer::HandleNewline()
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col, m_Source.End, m_Source.End);
		NextChar();
		return std::make_unique<Token>(TokenType::Newline, tokenSource);
	}

	std::unique_ptr<Token> Lexer::MakeEOFToken()
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col, m_Source.End, m_Source.End);
		return std::make_unique<Token>(TokenType::EndOfFile, tokenSource);
	}

	std::unique_ptr<Token> Lexer::MakeNumberToken()
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col, m_Source.End, m_Source.End);
		bool floatNumber = false;

		std::string numbers;
		for (char c = PeekChar(); IsDecimalNumber(c); c = PeekChar())
		{
			numbers.push_back(c);
			NextChar();
			if (!floatNumber && PeekChar() == '.')
			{
				numbers.push_back(NextChar());
				floatNumber = true;
			}
		}

		tokenSource.End = m_Source.End - 1;
		return (floatNumber ? std::make_unique<Token>((FloatType)std::atof(numbers.c_str()), tokenSource) : std::make_unique<Token>((IntegerType)std::atoll(numbers.c_str()), tokenSource));
	}

	std::unique_ptr<Token> Lexer::MakeNumberBaseToken()
	{
		if (m_Tokens.empty() || !(m_Tokens.back()->GetType() == TokenType::LiteralInteger && m_Tokens.back()->GetValue<IntegerType>() == 0))
			return MakeIdentifierToken();

		m_Tokens.pop_back();

		char baseType = PeekChar();
		if (baseType == 'x')
			return MakeHexNumberToken();
		else if (baseType == 'b')
			return MakeBinaryNumberToken();

		return {};
	}

	std::unique_ptr<Token> Lexer::MakeHexNumberToken()
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col - 1, m_Source.End - 1, m_Source.End - 1);
		NextChar();

		std::string hexStr{};
		for (char c = PeekChar(); IsHexNumber(c); c = PeekChar())
		{
			hexStr += c;
			NextChar();
		}

		tokenSource.End = m_Source.End - 1;
		return std::make_unique<Token>((IntegerType)std::strtol(hexStr.c_str(), 0, 16), tokenSource);
	}

	std::unique_ptr<Token> Lexer::MakeBinaryNumberToken()
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col - 1, m_Source.End - 1, m_Source.End - 1);
		NextChar();

		std::string binaryStr;
		for (char c = PeekChar(); c >= '0' && c <= '9'; c = PeekChar())
		{
			binaryStr.push_back(c);
			NextChar();
		}

		if (!IsBinaryNumber(binaryStr))
			throw Error::Exceptions::UnexpectedTokenException(("0b" + binaryStr), Error::ErrorType::LexerUnexpectedToken, tokenSource);

		tokenSource.End = m_Source.End - 1;
		return std::make_unique<Token>((IntegerType)std::strtol(binaryStr.c_str(), 0, 2), tokenSource);
	}

	std::unique_ptr<Token> Lexer::MakeStringToken(char sdelim, char edelim)
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col, m_Source.End, m_Source.End);
		if (NextChar() != sdelim)
			throw Error::Exceptions::UnexpectedTokenException(std::string{ sdelim }, Error::ErrorType::LexerUnexpectedToken, tokenSource);

		std::string str;
		for (char c = NextChar(); c != edelim && c != EOF; c = NextChar())
			str.push_back(c);

		tokenSource.End = m_Source.End - 1;
		return std::make_unique<Token>(str, tokenSource);
	}

	std::unique_ptr<Token> Lexer::MakeOperatorToken()
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col, m_Source.End, m_Source.End);
		bool singleOperator = true;

		char op = NextChar();
		std::string opStr{ op };

		if (op == '*' && PeekChar() == '=')
		{
			opStr += NextChar();
			singleOperator = false;
		}
		else if (!IsSinglyOperator(op))
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

		if ((opStr == "<<" || opStr == ">>") && PeekChar() == '=')
		{
			char eq = NextChar();
			opStr += eq;
		}

		// PutBack All Except First One
		if (!singleOperator && !IsValidOperator(opStr))
		{
			for (size_t i = opStr.size() - 1; i >= 1; i--)
				PutBack(opStr[i]);
			opStr = opStr[0];
		}

		if (singleOperator && !IsValidOperator(opStr))
			throw Error::Exceptions::UnexpectedTokenException(opStr, Error::ErrorType::LexerUnexpectedToken, tokenSource);

		tokenSource.End = m_Source.End - 1;
		return std::make_unique<Token>(StringToTokenType(opStr), tokenSource);
	}

	std::unique_ptr<Token> Lexer::MakeSymbolToken()
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col, m_Source.End, m_Source.End);
		char c = NextChar();
		return std::make_unique<Token>(StringToTokenType(std::string{ c }), tokenSource);
	}

	std::unique_ptr<Token> Lexer::MakeSpecialToken()
	{
		char c = PeekChar();
		if (std::isalpha(c) || c == '_')
			return MakeIdentifierToken();
		return {};
	}

	std::unique_ptr<Token> Lexer::MakeIdentifierToken()
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col, m_Source.End, m_Source.End);
		std::string identifier;

		for (char c = PeekChar(); ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'); c = PeekChar())
		{
			identifier += c;
			c = NextChar();
		}

		tokenSource.End = m_Source.End - 1;

		if (IsKeyword(identifier) && (identifier == "true" || identifier == "false"))
			return std::make_unique<Token>((identifier == "true" ? true : false), tokenSource);
		else if (IsKeyword(identifier) && identifier == "null")
			return std::make_unique<Token>(TokenType::LiteralNull, tokenSource);

		return std::make_unique<Token>((IsKeyword(identifier) ? StringToTokenType(identifier) : TokenType::Identifier), identifier, tokenSource);
	}

	std::unique_ptr<Token> Lexer::HandleSlashOperator()
	{
		char c = PeekChar();
		if (c == '/')
		{
			NextChar();

			if (PeekChar() == '/')
			{
				NextChar();
				return MakeSingleLineCommentToken();
			}
			else if (PeekChar() == '*')
			{
				NextChar();
				return MakeMultiLineCommentToken();
			}

			PutBack('/');
			m_Source.Col--;
			m_Source.End--;
			// Reverse Line Too?
			return MakeOperatorToken();
		}

		return {};
	}

	std::unique_ptr<Token> Lexer::MakeSingleLineCommentToken()
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col - 2, m_Source.End - 2, m_Source.End);
		std::string comment;
		for (char c = PeekChar(); (c != '\n' && c != EOF); c = PeekChar())
		{
			comment += c;
			c = NextChar();
		}
		tokenSource.End = m_Source.End - 1;
		return std::make_unique<Token>(TokenType::Comment, comment, tokenSource);
	}

	std::unique_ptr<Token> Lexer::MakeMultiLineCommentToken()
	{
		EyeSource tokenSource(m_Source.Source, m_Source.Type, m_Source.Line, m_Source.Col - 2, m_Source.End - 2, m_Source.End);
		std::string comment;

		while (true)
		{
			char c;
			for (c = PeekChar(); (c != '*' && c != EOF); c = PeekChar())
			{
				comment += c;
				c = NextChar();
			}

			if (c == EOF)
			{
				throw Error::Exceptions::UnexpectedTokenException(comment, Error::ErrorType::LexerUnexpectedToken, tokenSource);
			}
			else if (c == '*')
			{
				NextChar();
				if (PeekChar() == '/')
				{
					NextChar();
					break;
				}
			}
		}

		tokenSource.End = m_Source.End - 1;
		return std::make_unique<Token>(TokenType::Comment, comment, tokenSource);
	}

	bool Lexer::IsOperator(char op) const
	{
		return (op == '+' || op == '-' || op == '*' || op == '/' || op == '%' ||
			op == '=' || op == '<' || op == '>' || op == '!' ||
			op == '&' || op == '|' || op == '^' || op == '~' ||
			op == '[' || op == '(' || op == '?' || op == ',' || op == '.');
	}

	bool Lexer::IsSinglyOperator(char op) const
	{
		return (op == ',' || op == '(' || op == '[' || op == '?' || op == '*' || op == '.');
	}

	bool Lexer::IsValidOperator(const std::string& op) const
	{
		return (op == "+" || op == "-" || op == "*" || op == "/" || op == "%" || op == "++" || op == "--" ||
			op == "=" || op == "+=" || op == "-=" || op == "*=" || op == "/=" || op == "%=" || op == "&=" || op == "|=" || op == "^=" || op == "<<=" || op == ">>=" ||
			op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=" ||
			op == "&&" || op == "||" || op == "!" ||
			op == "&" || op == "|" || op == "^" || op == "<<" || op == ">>" || op == "~" ||
			op == "(" || op == "[" || op == "?" || op == "," || op == ".");
	}

	bool Lexer::IsDecimalNumber(char num)
	{
		return (num >= '0' && num <= '9');
	}

	bool Lexer::IsHexNumber(char num) const
	{
		num = std::tolower(num);
		return ((num >= '0' && num <= '9') || (num >= 'a' && num <= 'f'));
	}

	bool Lexer::IsBinaryNumber(const std::string& num) const
	{
		for (const auto& n : num)
			if (n != '0' && n != '1')
				return false;
		return true;
	}

	bool Lexer::IsKeyword(const std::string& str) const
	{
		static const std::vector keywords = {
			"int", "float", "str", "bool", "void",
			"const", "true", "false", "null",
			"if",	"else",
			"while", "do", "for", "continue", "break",
			"function", "return",
		};

		return (std::find(keywords.begin(), keywords.end(), str) != keywords.end());
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
		char c = m_BufferStream.get();
		m_Source.End++;
		m_Source.Col++;
		if (c == '\n')
		{
			m_Source.Line++;
			m_Source.Col = 1;
		}
		return c;
	}

	char Lexer::PeekChar()
	{
		return m_BufferStream.peek();
	}

	void Lexer::PutBack(char c)
	{
		m_BufferStream.putback(c);
	}
}
