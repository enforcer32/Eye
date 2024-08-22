#include "EYELexer/Token.h"

namespace Eye
{
	namespace Lexer
	{
		Token::Token()
			: m_Type(TokenType::Invalid)
		{
		}

		Token::Token(IntegerType value, Position position)
			: m_Type(TokenType::LiteralInteger), m_Value(value), m_Position(position)
		{
		}

		Token::Token(FloatType value, Position position)
			: m_Type(TokenType::LiteralFloat), m_Value(value), m_Position(position)
		{
		}

		Token::Token(StringType value, Position position)
			: m_Type(TokenType::LiteralString), m_Value(value), m_Position(position)
		{
		}

		Token::Token(BooleanType value, Position position)
			: m_Type(TokenType::LiteralBoolean), m_Value(value), m_Position(position)
		{
		}

		Token::Token(TokenType type, Position position)
			: m_Type(type), m_Position(position)
		{
		}

		Token::Token(TokenType type, StringType value, Position position)
			: m_Type(type), m_Value(value), m_Position(position)
		{
		}

		bool Token::operator==(const Token& token) const
		{
			if (m_Type != token.m_Type)
				return false;

			switch (token.m_Type)
			{
			case TokenType::LiteralInteger:
				return std::get<IntegerType>(m_Value) == std::get<IntegerType>(token.m_Value);
			case TokenType::LiteralFloat:
				return std::get<FloatType>(m_Value) == std::get<FloatType>(token.m_Value);
			case TokenType::LiteralString:
				return std::get<StringType>(m_Value) == std::get<StringType>(token.m_Value);
			case TokenType::LiteralBoolean:
				return std::get<BooleanType>(m_Value) == std::get<BooleanType>(token.m_Value);
			case TokenType::Comment:
				return std::get<StringType>(m_Value) == std::get<StringType>(token.m_Value);
			default:
				break;
			}

			return true;
		}

		bool Token::operator!=(const Token& token) const
		{
			return !(*this == token);
		}

		Token::operator bool() const
		{
			return m_Type != TokenType::Invalid;
		}

		TokenType Token::GetType() const
		{
			return m_Type;
		}

		std::string Token::ToString() const
		{
			std::string type = "Invalid";
			std::string value = "None";

			switch (m_Type)
			{
			case TokenType::LiteralInteger:
				type = "LiteralInteger";
				value = std::to_string(std::get<IntegerType>(m_Value));
				break;
			case TokenType::LiteralFloat:
				type = "LiteralFloat";
				value = std::to_string(std::get<FloatType>(m_Value));
				break;
			case TokenType::LiteralString:
				type = "LiteralString";
				value = std::get<StringType>(m_Value);
				break;
			case TokenType::LiteralBoolean:
				type = "LiteralBoolean";
				value = (std::get<BooleanType>(m_Value) ? "true" : "false");
				break;
			case TokenType::LiteralNull:
				type = "LiteralNull";
				value = "null";
				break;
			case TokenType::Identifier:
				type = "Identifier";
				value = std::get<StringType>(m_Value);
				break;
			case TokenType::KeywordAuto:
			case TokenType::KeywordInt:
			case TokenType::KeywordFloat:
			case TokenType::KeywordStr:
			case TokenType::KeywordBool:
			case TokenType::KeywordConst:
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
				value = TokenTypeStr[(int)m_Type];
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
				value = TokenTypeStr[(int)m_Type];
				break;
			case TokenType::SymbolRightParenthesis:
			case TokenType::SymbolRightBracket:
			case TokenType::SymbolLeftBrace:
			case TokenType::SymbolRightBrace:
			case TokenType::SymbolColon:
			case TokenType::SymbolSemiColon:
			case TokenType::SymbolBackslash:
				type = "Symbol";
				value = TokenTypeStr[(int)m_Type];
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

			return "Token{Type: " + type + ", Value: " + value + ", " + m_Position.ToString() + "}";
		}
	}
}
