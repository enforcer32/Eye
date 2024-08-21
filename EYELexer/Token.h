#pragma once

#include <string>
#include <variant>
#include <ostream>

namespace Eye
{
	namespace Lexer
	{
		using Integer = unsigned long long;
		using Float = double;
		using String = const char*;
		using Boolean = bool;

		struct Position
		{
			uint32_t Line = 1;
			uint32_t Col = 1;
			std::string FileName = "";

			std::string ToString() const
			{
				return "Position: {Line: " + std::to_string(Line) + ", Column: " + std::to_string(Col) + ", FileName: " + FileName + "}";
			}
		};

		const char* TokenTypeStr[]
		{
			"Invalid",
			// Literals
			"LiteralInteger",
			"LiteralFloat",
			"LiteralString",
			"LiteralBoolean",
			"LiteralNull",
			// Identifier & Keyword
			"Identifier",
			"auto",
			"int",
			"float",
			"str",
			"bool",
			"const",
			"true",
			"false",
			"null",
			"If",
			"else",
			"while",
			"do",
			"for",
			"continue",
			"break",
			"return",
			"new",
			"function",
			"struct",
			// Operators
			"+",
			"-",
			"*",
			"/",
			"%",
			"++",
			"--",
			"=",
			"+=",
			"-=",
			"*=",
			"/=",
			"%=",
			"&=",
			"|=",
			"^=",
			">>=",
			"<<=",
			"==",
			"!=",
			"<",
			">",
			"<=",
			">=",
			"&&",
			"||",
			"!",
			"&",
			"|",
			"^",
			">>",
			"<<",
			"~",
			"(",
			"[",
			"?",
			".",
			",",
			// Symbols
			")",
			"]",
			"{",
			"}",
			":",
			";",
			"\\",
			// Others
			"Comment",
			"Newline",
			"EscapeCharacter",
			"EndOfFile",
		};

		enum class TokenType
		{
			Invalid,
			// Literals
			LiteralInteger,
			LiteralFloat,
			LiteralString,
			LiteralBoolean,
			LiteralNull,
			// Identifier & Keyword
			Identifier,
			KeywordAuto,
			KeywordInt,
			KeywordFloat,
			KeywordStr,
			KeywordBool,
			KeywordConst,
			KeywordTrue,
			KeywordFalse,
			KeywordNull,
			KeywordIf,
			KeywordElse,
			KeywordWhile,
			KeywordDo,
			KeywordFor,
			KeywordContinue,
			KeywordBreak,
			KeywordReturn,
			KeywordNew,
			KeywordFunction,
			KeywordStruct,
			// Operators
			OperatorPlus,
			OperatorMinus,
			OperatorStar,
			OperatorSlash,
			OperatorModulo,
			OperatorIncrement,
			OperatorDecrement,
			OperatorAssignment,
			OperatorAssignmentPlus,
			OperatorAssignmentMinus,
			OperatorAssignmentStar,
			OperatorAssignmentSlash,
			OperatorAssignmentModulo,
			OperatorAssignmentBitwiseAND,
			OperatorAssignmentBitwiseOR,
			OperatorAssignmentBitwiseXOR,
			OperatorAssignmentBitshiftRight,
			OperatorAssignmentBitshiftLeft,
			OperatorEquals,
			OperatorNotEquals,
			OperatorSmaller,
			OperatorGreater,
			OperatorSmallerEquals,
			OperatorGreaterEquals,
			OperatorLogicalAND,
			OperatorLogicalOR,
			OperatorNegate,
			OperatorBitwiseAND,
			OperatorBitwiseOR,
			OperatorBitwiseXOR,
			OperatorBitshiftRight,
			OperatorBitshiftLeft,
			OperatorBitwiseNOT,
			OperatorLeftParenthesis,
			OperatorLeftBracket,
			OperatorQuestionMark,
			OperatorDot,
			OperatorComma,
			// Symbols
			SymbolRightParenthesis,
			SymbolRightBracket,
			SymbolLeftBrace,
			SymbolRightBrace,
			SymbolColon,
			SymbolSemiColon,
			SymbolBackslash,
			// Others
			Comment,
			Newline,
			EscapeCharacter,
			EndOfFile,
		};

		struct Token
		{
			TokenType Type;
			Position Pos;
			std::variant<Integer, Float, String, Boolean> Value;
		
			Token(Integer value, Position pos)
				: Type(TokenType::LiteralInteger), Value(value), Pos(pos)
			{
			}

			Token(Float value, Position pos)
				: Type(TokenType::LiteralFloat), Value(value), Pos(pos)
			{
			}

			Token(String value, Position pos)
				: Type(TokenType::LiteralString), Value(value), Pos(pos)
			{
			}

			Token(Boolean value, Position pos)
				: Type(TokenType::LiteralBoolean), Value(value), Pos(pos)
			{
			}

			Token(TokenType type, Position pos)
				: Type(type), Pos(pos)
			{
			}

			bool operator==(const Token& token) const
			{
				if (Type != token.Type)
					return false;

				switch (token.Type)
				{
				case TokenType::LiteralInteger:
					return std::get<Integer>(Value) == std::get<Integer>(token.Value);
				case TokenType::LiteralFloat:
					return std::get<Float>(Value) == std::get<Float>(token.Value);
				case TokenType::LiteralString:
					return std::get<String>(Value) == std::get<String>(token.Value);
				case TokenType::LiteralBoolean:
					return std::get<Boolean>(Value) == std::get<Boolean>(token.Value);
				case TokenType::Comment:
					return std::get<String>(Value) == std::get<String>(token.Value);
				default:
					break;
				}

				return true;
			}

			bool operator!=(const Token& token)
			{
				return !(*this == token);
			}

			operator bool() const
			{
				return Type != TokenType::Invalid;
			}

			std::string ToString() const
			{
				std::string type = "Invalid";
				std::string value = "None";

				switch (Type)
				{
				case TokenType::LiteralInteger:
					type = "LiteralInteger";
					value = std::to_string(std::get<Integer>(Value));
					break;
				case TokenType::LiteralFloat:
					type = "LiteralFloat";
					value = std::to_string(std::get<Float>(Value));
					break;
				case TokenType::LiteralString:
					type = "LiteralString";
					value = std::get<String>(Value);
					break;
				case TokenType::LiteralBoolean:
					type = "LiteralBoolean";
					value = std::to_string(std::get<Boolean>(Value));
					break;
				case TokenType::LiteralNull:
					type = "LiteralNull";
					value = "null";
					break;
				case TokenType::Identifier:
					type = "Identifier";
					value = std::get<String>(Value);
					break;
				case TokenType::KeywordAuto:
				case TokenType::KeywordInt:
				case TokenType::KeywordFloat:
				case TokenType::KeywordStr:
				case TokenType::KeywordBool:
				case TokenType::KeywordConst:
				case TokenType::KeywordTrue:
				case TokenType::KeywordFalse:
				case TokenType::KeywordNull:
				case TokenType::KeywordIf:
				case TokenType::KeywordElse:
				case TokenType::KeywordWhile:
				case TokenType::KeywordDo:
				case TokenType::KeywordFor:
				case TokenType::KeywordContinue:
				case TokenType::KeywordBreak:
				case TokenType::KeywordReturn:
				case TokenType::KeywordNew:
				case TokenType::KeywordFunction:
				case TokenType::KeywordStruct:
					type = "Keyword";
					value = TokenTypeStr[(int)Type];
					break;
				case TokenType::OperatorPlus:
				case TokenType::OperatorMinus:
				case TokenType::OperatorStar:
				case TokenType::OperatorSlash:
				case TokenType::OperatorModulo:
				case TokenType::OperatorIncrement:
				case TokenType::OperatorDecrement:
				case TokenType::OperatorAssignment:
				case TokenType::OperatorAssignmentPlus:
				case TokenType::OperatorAssignmentMinus:
				case TokenType::OperatorAssignmentStar:
				case TokenType::OperatorAssignmentSlash:
				case TokenType::OperatorAssignmentModulo:
				case TokenType::OperatorAssignmentBitwiseAND:
				case TokenType::OperatorAssignmentBitwiseOR:
				case TokenType::OperatorAssignmentBitwiseXOR:
				case TokenType::OperatorAssignmentBitshiftRight:
				case TokenType::OperatorAssignmentBitshiftLeft:
				case TokenType::OperatorEquals:
				case TokenType::OperatorNotEquals:
				case TokenType::OperatorSmaller:
				case TokenType::OperatorGreater:
				case TokenType::OperatorSmallerEquals:
				case TokenType::OperatorGreaterEquals:
				case TokenType::OperatorLogicalAND:
				case TokenType::OperatorLogicalOR:
				case TokenType::OperatorNegate:
				case TokenType::OperatorBitwiseAND:
				case TokenType::OperatorBitwiseOR:
				case TokenType::OperatorBitwiseXOR:
				case TokenType::OperatorBitshiftRight:
				case TokenType::OperatorBitshiftLeft:
				case TokenType::OperatorBitwiseNOT:
				case TokenType::OperatorLeftParenthesis:
				case TokenType::OperatorLeftBracket:
				case TokenType::OperatorQuestionMark:
				case TokenType::OperatorDot:
				case TokenType::OperatorComma:
					type = "Operator";
					value = TokenTypeStr[(int)Type];
					break;
				case TokenType::SymbolRightParenthesis:
				case TokenType::SymbolRightBracket:
				case TokenType::SymbolLeftBrace:
				case TokenType::SymbolRightBrace:
				case TokenType::SymbolColon:
				case TokenType::SymbolSemiColon:
				case TokenType::SymbolBackslash:
					type = "Symbol";
					value = TokenTypeStr[(int)Type];
					break;
				case TokenType::Comment:
					type = "Comment";
					break;
				case TokenType::Newline:
					type = "Newline";
					break;
				case TokenType::EscapeCharacter:
					type = "EscapeCharacter";
					break;
				case TokenType::EndOfFile:
					type = "EndOfFile";
					break;
				default:
					break;
				}
				
				return "Token{Type: " + type + ", Value: " + value + ", " + Pos.ToString() + "}";
			}
		};
	}
}
