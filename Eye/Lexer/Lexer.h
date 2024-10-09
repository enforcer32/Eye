#pragma once

#include "Eye/Lexer/Token.h"
#include "Eye/Error/Error.h"
#include "Eye/Utility/EyeSource.h"

#include <sstream>
#include <vector>
#include <expected>

namespace Eye
{
	class Lexer
	{
	public:
		std::expected<std::vector<std::unique_ptr<Token>>, Error::Error> Tokenize(const EyeSource& source);

	private:
		std::unique_ptr<Token> NextToken();
		std::unique_ptr<Token> HandleWhitespace();
		std::unique_ptr<Token> HandleNewline();
		std::unique_ptr<Token> MakeEOFToken();
		std::unique_ptr<Token> MakeNumberToken();
		std::unique_ptr<Token> MakeNumberBaseToken();
		std::unique_ptr<Token> MakeHexNumberToken();
		std::unique_ptr<Token> MakeBinaryNumberToken();
		std::unique_ptr<Token> MakeStringToken(char sdelim, char edelim);
		std::unique_ptr<Token> MakeOperatorToken();
		std::unique_ptr<Token> MakeSymbolToken();
		std::unique_ptr<Token> MakeSpecialToken();
		std::unique_ptr<Token> MakeIdentifierToken();
		std::unique_ptr<Token> HandleSlashOperator();
		std::unique_ptr<Token> MakeSingleLineCommentToken();
		std::unique_ptr<Token> MakeMultiLineCommentToken();

	private:
		bool IsOperator(char op) const;
		bool IsSinglyOperator(char op) const;
		bool IsValidOperator(const std::string& op) const;
		bool IsDecimalNumber(char num);
		bool IsHexNumber(char num) const;
		bool IsBinaryNumber(const std::string& num) const;
		bool IsKeyword(const std::string& op) const;
		char CharToEscapedChar(char c) const;

	private:
		char NextChar();
		char PeekChar();
		void PutBack(char c);

	private:
		EyeSource m_Source;
		std::istringstream m_BufferStream;
		std::vector<std::unique_ptr<Token>> m_Tokens;
	};
}
