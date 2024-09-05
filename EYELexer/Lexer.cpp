#include "EYELexer/Lexer.h"

#include <EYEUtility/FileIO.h>
#include <EYEUtility/Logger.h>
#include <EYEError/Exceptions/UnexpectedTokenException.h>

namespace Eye
{
	namespace Lexer
	{
		std::expected<bool, Error::Error> Lexer::Tokenize(const std::string& filepath)
		{
			m_FilePosition.FilePath = filepath;
			m_BufferStream = std::istringstream(FileIO::ReadFileContent(filepath));;

			try
			{
				std::shared_ptr<Token> token = NextToken();
				while (token)
				{
					m_Tokens.push_back(token);
					token = NextToken();
				}
			}
			catch (const Error::Exceptions::UnexpectedTokenException& ex)
			{
				return std::unexpected(Error::Error(Error::ErrorType::LexerUnexpectedToken, ex.what()));
			}
			catch (...)
			{
				EYE_LOG_CRITICAL("EYELexer->Tokenize Unknown Exception!");
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
					throw Error::Exceptions::UnexpectedTokenException(std::string{ c }, m_FilePosition);
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
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col, m_FilePosition.Offset, m_FilePosition.Offset, m_FilePosition.FilePath);
			NextChar();
			return std::make_shared<Token>(TokenType::Newline, location);
		}

		std::shared_ptr<Token> Lexer::MakeEOFToken()
		{
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col, m_FilePosition.Offset, m_FilePosition.Offset, m_FilePosition.FilePath);
			return std::make_shared<Token>(TokenType::EndOfFile, location);
		}

		std::shared_ptr<Token> Lexer::MakeNumberToken()
		{
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col, m_FilePosition.Offset, m_FilePosition.Offset, m_FilePosition.FilePath);
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

			location.End = m_FilePosition.Offset - 1;
			return (floatNumber ? std::make_shared<Token>((FloatType)std::atof(numbers.c_str()), location) : std::make_shared<Token>((IntegerType)std::atoll(numbers.c_str()), location));
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
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col-1, m_FilePosition.Offset - 1, m_FilePosition.Offset - 1, m_FilePosition.FilePath);
			NextChar();

			std::string hexStr{};
			for (char c = PeekChar(); IsHexNumber(c); c = PeekChar())
			{
				hexStr += c;
				NextChar();
			}

			location.End = m_FilePosition.Offset - 1;
			return std::make_shared<Token>((IntegerType)std::strtol(hexStr.c_str(), 0, 16), location);
		}

		std::shared_ptr<Token> Lexer::MakeBinaryNumberToken()
		{
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col - 1, m_FilePosition.Offset - 1, m_FilePosition.Offset - 1, m_FilePosition.FilePath);
			NextChar();

			std::string binaryStr;
			for (char c = PeekChar(); c >= '0' && c <= '9'; c = PeekChar())
			{
				binaryStr.push_back(c);
				NextChar();
			}

			if (!IsBinaryNumber(binaryStr))
				throw Error::Exceptions::UnexpectedTokenException(("0b" + binaryStr), m_FilePosition);

			location.End = m_FilePosition.Offset - 1;
			return std::make_shared<Token>((IntegerType)std::strtol(binaryStr.c_str(), 0, 2), location);
		}

		std::shared_ptr<Token> Lexer::MakeStringToken(char sdelim, char edelim)
		{
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col, m_FilePosition.Offset, m_FilePosition.Offset, m_FilePosition.FilePath);
			if (NextChar() != sdelim)
				throw Error::Exceptions::UnexpectedTokenException(std::string{ sdelim }, m_FilePosition);

			std::string str;
			for (char c = NextChar(); c != edelim && c != EOF; c = NextChar())
				str.push_back(c);

			location.End = m_FilePosition.Offset - 1;
			return std::make_shared<Token>(str, location);
		}

		std::shared_ptr<Token> Lexer::MakeOperatorToken()
		{
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col, m_FilePosition.Offset, m_FilePosition.Offset, m_FilePosition.FilePath);
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
				throw Error::Exceptions::UnexpectedTokenException(opStr, m_FilePosition);

			location.End = m_FilePosition.Offset - 1;
			return std::make_shared<Token>(StringToTokenType(opStr), location);
		}

		std::shared_ptr<Token> Lexer::MakeSymbolToken()
		{
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col, m_FilePosition.Offset, m_FilePosition.Offset, m_FilePosition.FilePath);
			char c = NextChar();
			return std::make_shared<Token>(StringToTokenType(std::string{ c }), location);
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
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col, m_FilePosition.Offset, m_FilePosition.Offset, m_FilePosition.FilePath);
			std::string identifier;

			for (char c = PeekChar(); ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'); c = PeekChar())
			{
				identifier += c;
				c = NextChar();
			}

			location.End = m_FilePosition.Offset - 1;

			if (IsKeyword(identifier) && (identifier == "true" || identifier == "false"))
				return std::make_shared<Token>((identifier == "true" ? true : false), location);
			else if (IsKeyword(identifier) && identifier == "null")
				return std::make_shared<Token>(TokenType::LiteralNull, location);

			return std::make_shared<Token>((IsKeyword(identifier) ? StringToTokenType(identifier) : TokenType::Identifier), identifier, location);
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
				m_FilePosition.Col--;
				m_FilePosition.Offset--;
				// Reverse Line Too?
				return MakeOperatorToken();
			}

			return {};
		}

		std::shared_ptr<Token> Lexer::MakeSingleLineCommentToken()
		{
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col - 2, m_FilePosition.Offset - 2, m_FilePosition.Offset, m_FilePosition.FilePath);
			std::string comment;
			for (char c = PeekChar(); (c != '\n' && c != EOF); c = PeekChar())
			{
				comment += c;
				c = NextChar();
			}
			location.End = m_FilePosition.Offset - 1;
			return std::make_shared<Token>(TokenType::Comment, comment, location);
		}

		std::shared_ptr<Token> Lexer::MakeMultiLineCommentToken()
		{
			Types::Location location(m_FilePosition.Line, m_FilePosition.Col - 2, m_FilePosition.Offset - 2, m_FilePosition.Offset, m_FilePosition.FilePath);
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
					throw Error::Exceptions::UnexpectedTokenException(comment, m_FilePosition);
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

			location.End = m_FilePosition.Offset - 1;
			return std::make_shared<Token>(TokenType::Comment, comment, location);
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
			m_FilePosition.Offset++;
			m_FilePosition.Col++;
			if (c == '\n')
			{
				m_FilePosition.Line++;
				m_FilePosition.Col = 1;
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
