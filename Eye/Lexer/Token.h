#pragma once

#include "Eye/Common/Common.h"

#include <iostream>

namespace EYE
{
	enum class TokenType
	{
		Invalid,
		Keyword,
		Identifier,
		Operator,
		Symbol,
		Number,
		String,
		Comment,
		Newline,
		EscapeCharacter,
		EndOfFile,
	};

	struct Token
	{
		TokenType Type = TokenType::Invalid;
		Position Position;
		union
		{
			char Char;
			const char* String;
			unsigned long long Number;
			void* Any;
		};

		Token()
			: Any(nullptr)
		{
		}

		operator bool()
		{
			return Type != TokenType::Invalid;
		}

		friend std::ostream& operator<<(std::ostream& os, const Token& token)
		{
			std::string type;
			std::string value = "None";

			switch (token.Type)
			{
			case TokenType::Invalid:
				type = "Invalid";
				break;
			case TokenType::Keyword:
				type = "Keyword";
				value = token.String;
				break;
			case TokenType::Identifier:
				type = "Identifier";
				value = token.String;
				break;
			case TokenType::Operator:
				type = "Operator";
				value = token.String;
				break;
			case TokenType::Symbol:
				type = "Symbol";
				value = token.Char;
				break;
			case TokenType::Number:
				type = "Number";
				value = std::to_string(token.Number);
				break;
			case TokenType::String:
				type = "String";
				value = token.String;
				break;
			case TokenType::Comment:
				type = "Comment";
				value = token.String;
				break;
			case TokenType::Newline:
				type = "Newline";
				break;
			case TokenType::EndOfFile:
				type = "EndOfFile";
				break;
			case TokenType::EscapeCharacter:
				type = "EscapeCharacter";
				value = "NotPrintable";
				break;
			default:
				type = "UNKNOWN";
				break;
			}

			os << "Token{Type: " << type << ", Value: " << value << ", Position: {Line: " << token.Position.Line << ", Column: " << token.Position.Col << ", FileName: " << token.Position.FileName << "}";
			return os;
		}
	};
}
