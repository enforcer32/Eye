#include "Eye/Lexer/Lexer.h"

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

		default:
			break;
		}

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
