#include "EYELexer/Lexer.h"

#include <EYEUtility/FileIO.h>
#include <EYEUtility/Logger.h>

#define EYELEXER_THROW_UNEXPECTED_TOKEN(token, line, col, filename) EYE_LOG_CRITICAL("EYELexer->Unexpected Token : {}\n\t on line {}, col {} in file {}", token, line, col, filename);

namespace Eye
{
	namespace Lexer
	{
		bool Lexer::Tokenize(const std::string& filepath)
		{
			m_Position.FileName = filepath;
			m_BufferStream = std::istringstream(FileIO::ReadFileContent(filepath));;

			std::shared_ptr<Token> token = NextToken();
			while (token)
			{
				m_Tokens.push_back(token);
				token = NextToken();
			}

			m_Tokens.push_back(MakeEOFToken());
			return true;
		}

		std::vector<std::shared_ptr<Token>> Lexer::GetTokens() const
		{
			return m_Tokens;
		}

		std::shared_ptr<Token> Lexer::NextToken()
		{
			std::shared_ptr<Token> token;

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
					EYELEXER_THROW_UNEXPECTED_TOKEN(c, m_Position.Line, m_Position.Col, m_Position.FileName);
				break;
			}

			return token;
		}

		std::shared_ptr<Token> Lexer::HandleWhitespace()
		{
			NextChar();
			return NextToken();
		}

		std::shared_ptr<Token> Lexer::HandleNewline()
		{
			NextChar();
			return std::make_shared<Token>(TokenType::Newline, m_Position);
		}

		std::shared_ptr<Token> Lexer::MakeEOFToken()
		{
			return std::make_shared<Token>(TokenType::EndOfFile, m_Position);
		}

		std::shared_ptr<Token> Lexer::MakeNumberToken()
		{
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

			return (floatNumber ? std::make_shared<Token>((FloatType)std::atof(numbers.c_str()), m_Position) : std::make_shared<Token>((IntegerType)std::atoll(numbers.c_str()), m_Position));
		}

		std::shared_ptr<Token> Lexer::MakeNumberBaseToken()
		{
			if (m_Tokens.empty() || !(m_Tokens.back()->GetType() == TokenType::LiteralInteger && m_Tokens.back()->GetValue<IntegerType>() == 0))
				return MakeIdentifierToken();

			std::shared_ptr<Token> lastToken = m_Tokens.back();
			m_Tokens.pop_back();

			char baseType = PeekChar();
			if (baseType == 'x')
				return MakeHexNumberToken();
			else if (baseType == 'b')
				return MakeBinaryNumberToken();

			return {};
		}

		std::shared_ptr<Token> Lexer::MakeHexNumberToken()
		{
			NextChar();

			std::string hexStr{};
			for (char c = PeekChar(); IsHexNumber(c); c = PeekChar())
			{
				hexStr += c;
				NextChar();
			}

			return std::make_shared<Token>((IntegerType)std::strtol(hexStr.c_str(), 0, 16), m_Position);
		}

		std::shared_ptr<Token> Lexer::MakeBinaryNumberToken()
		{
			NextChar();

			std::string binaryStr;
			for (char c = PeekChar(); c >= '0' && c <= '9'; c = PeekChar())
			{
				binaryStr.push_back(c);
				NextChar();
			}

			if (!IsBinaryNumber(binaryStr))
				EYELEXER_THROW_UNEXPECTED_TOKEN(("0b" + binaryStr), m_Position.Line, m_Position.Col, m_Position.FileName);

			return std::make_shared<Token>((IntegerType)std::strtol(binaryStr.c_str(), 0, 2), m_Position);
		}

		std::shared_ptr<Token> Lexer::MakeStringToken(char sdelim, char edelim)
		{
			if (NextChar() != sdelim)
				EYELEXER_THROW_UNEXPECTED_TOKEN(sdelim, m_Position.Line, m_Position.Col, m_Position.FileName);

			std::string str;
			for (char c = NextChar(); c != edelim && c != EOF; c = NextChar())
				str.push_back(c);

			return std::make_shared<Token>(str, m_Position);
		}

		std::shared_ptr<Token> Lexer::MakeOperatorToken()
		{
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
				EYELEXER_THROW_UNEXPECTED_TOKEN(opStr, m_Position.Line, m_Position.Col, m_Position.FileName);

			return std::make_shared<Token>(StringToTokenType(opStr), m_Position);
		}

		std::shared_ptr<Token> Lexer::MakeSymbolToken()
		{
			char c = NextChar();
			return std::make_shared<Token>(StringToTokenType(std::string{ c }), m_Position);
		}

		std::shared_ptr<Token> Lexer::MakeSpecialToken()
		{
			char c = PeekChar();
			if (std::isalpha(c) || c == '_')
				return MakeIdentifierToken();
			return {};
		}

		std::shared_ptr<Token> Lexer::MakeIdentifierToken()
		{
			std::string identifier;

			for (char c = PeekChar(); ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'); c = PeekChar())
			{
				identifier += c;
				c = NextChar();
			}

			if (IsKeyword(identifier) && (identifier == "true" || identifier == "false"))
				return std::make_shared<Token>((identifier == "true" ? true : false), m_Position);
			else if (IsKeyword(identifier) && identifier == "null")
				return std::make_shared<Token>(TokenType::LiteralNull, m_Position);

			return std::make_shared<Token>((IsKeyword(identifier) ? StringToTokenType(identifier) : TokenType::Identifier), identifier, m_Position);
		}

		std::shared_ptr<Token> Lexer::HandleSlashOperator()
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
				return MakeOperatorToken();
			}

			return {};
		}

		std::shared_ptr<Token> Lexer::MakeSingleLineCommentToken()
		{
			std::string comment;
			for (char c = PeekChar(); (c != '\n' && c != EOF); c = PeekChar())
			{
				comment += c;
				c = NextChar();
			}
			return std::make_shared<Token>(TokenType::Comment, comment, m_Position);
		}

		std::shared_ptr<Token> Lexer::MakeMultiLineCommentToken()
		{
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
					EYELEXER_THROW_UNEXPECTED_TOKEN(comment, m_Position.Line, m_Position.Col, m_Position.FileName);
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

			return std::make_shared<Token>(TokenType::Comment, comment, m_Position);
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
			m_Position.Col++;
			if (c == '\n')
			{
				m_Position.Line++;
				m_Position.Col = 1;
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
}
