#pragma once

#include "Eye/Common/Eye.h"
#include "Eye/Lexer/Token.h"

#include <vector>

namespace EYE
{
	enum class LexerResult
	{
		Successful,
		Failed
	};

	class Lexer
	{
	public:
		LexerResult Tokenize(EyeInstance* eyeInstance);

		// Temporary
		void DebugPrintTokens() const;

	private:
		Token NextToken();
		Token MakeNumberToken();

	private:
		char NextChar();
		char PeekChar() const;
		void PutBack(char c);

	private:
		EyeInstance* m_EyeInstance;
		Position m_Position;
		std::vector<Token> m_Tokens;
	};
}
