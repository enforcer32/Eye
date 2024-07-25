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
		Token HandleWhitespace();
		Token HandleNewline();
		Token MakeNumberToken();
		Token MakeStringToken(char sdelim, char edelim);
		Token MakeOperatorToken();
		Token MakeSymbolToken();

	private:
		bool IsOperator(char op) const;
		bool IsSinglyOperator(char op) const;
		bool IsValidOperator(const std::string& op) const;

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
