#pragma once

#include "EYELexer/Token.h"

#include <EYEError/Error.h>
#include <EYETypes/Position.h>

#include <sstream>
#include <vector>
#include <expected>

namespace Eye
{
	namespace Lexer
	{
		class Lexer
		{
		public:
			std::expected<bool, Error::Error> Tokenize(const std::string& filepath);
			std::vector<std::shared_ptr<Token>> GetTokens() const;

		private:
			std::shared_ptr<Token> NextToken();
			std::shared_ptr<Token> HandleWhitespace();
			std::shared_ptr<Token> HandleNewline();
			std::shared_ptr<Token> MakeEOFToken();
			std::shared_ptr<Token> MakeNumberToken();
			std::shared_ptr<Token> MakeNumberBaseToken();
			std::shared_ptr<Token> MakeHexNumberToken();
			std::shared_ptr<Token> MakeBinaryNumberToken();
			std::shared_ptr<Token> MakeStringToken(char sdelim, char edelim);
			std::shared_ptr<Token> MakeOperatorToken();
			std::shared_ptr<Token> MakeSymbolToken();
			std::shared_ptr<Token> MakeSpecialToken();
			std::shared_ptr<Token> MakeIdentifierToken();
			std::shared_ptr<Token> HandleSlashOperator();
			std::shared_ptr<Token> MakeSingleLineCommentToken();
			std::shared_ptr<Token> MakeMultiLineCommentToken();

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
			Types::Position m_FilePosition;
			std::istringstream m_BufferStream;
			std::vector<std::shared_ptr<Token>> m_Tokens;
		};
	}
}
