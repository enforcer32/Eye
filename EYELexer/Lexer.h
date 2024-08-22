#pragma once

#include "EYELexer/Token.h"

#include <sstream>
#include <vector>

namespace Eye
{
	namespace Lexer
	{
		class Lexer
		{
		public:
			bool Tokenize(const std::string& filepath);
			std::vector<Token> GetTokens() const;

		private:
			Token NextToken();
			Token HandleWhitespace();
			Token HandleNewline();
			Token MakeEOFToken();
			Token MakeNumberToken();
			Token MakeNumberBaseToken();
			Token MakeHexNumberToken();
			Token MakeBinaryNumberToken();
			Token MakeStringToken(char sdelim, char edelim);
			Token MakeOperatorToken();
			Token MakeSymbolToken();
			Token MakeSpecialToken();
			Token MakeIdentifierToken();
			Token HandleSlashOperator();
			Token MakeSingleLineCommentToken();
			Token MakeMultiLineCommentToken();

		private:
			bool IsOperator(char op) const;
			bool IsSinglyOperator(char op) const;
			bool IsValidOperator(const std::string& op) const;
			bool IsDecimalNumber(char num);
			bool IsHexNumber(char num) const;
			bool IsBinaryNumber(const std::string& num) const;
			bool IsKeyword(const std::string& op) const;
			char CharToEscapedChar(char c) const;
			TokenType OperatorToTokenType(const std::string& op) const;
			TokenType SymbolToTokenType(const std::string& symbol) const;
			TokenType KeywordToTokenType(const std::string& keyword) const;

		private:
			char NextChar();
			char PeekChar();
			void PutBack(char c);

		private:
			Position m_Position;
			std::istringstream m_BufferStream;
			std::vector<Token> m_Tokens;
		};
	}
}
