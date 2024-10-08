#include "Eye/Lexer/Token.h"

namespace Eye
{
	static const char* TokenTypeStr[]
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
		"int",
		"float",
		"str",
		"bool",
		"void",
		"const",
		"if",
		"else",
		"while",
		"do",
		"for",
		"continue",
		"break",
		"function",
		"return",
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
		"<<=",
		">>=",
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
		"<<",
		">>",
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

	std::string_view TokenTypeToString(TokenType type)
	{
		return TokenTypeStr[(int)type];
	}

	TokenType StringToTokenType(const std::string& str)
	{
		for (size_t i = 0; i < sizeof(TokenTypeStr) / sizeof(TokenTypeStr[0]); i++)
			if (str == TokenTypeStr[i])
				return (TokenType)i;
		return TokenType::Invalid;
	}

	Token::Token()
		: m_Type(TokenType::Invalid)
	{
	}

	Token::Token(IntegerType value, const EyeSource& source)
		: m_Type(TokenType::LiteralInteger), m_Value(value), m_Source(source)
	{
	}

	Token::Token(FloatType value, const EyeSource& source)
		: m_Type(TokenType::LiteralFloat), m_Value(value), m_Source(source)
	{
	}

	Token::Token(StringType value, const EyeSource& source)
		: m_Type(TokenType::LiteralString), m_Value(value), m_Source(source)
	{
	}

	Token::Token(BooleanType value, const EyeSource& source)
		: m_Type(TokenType::LiteralBoolean), m_Value(value), m_Source(source)
	{
	}

	Token::Token(TokenType type, const EyeSource& source)
		: m_Type(type), m_Source(source)
	{
	}

	Token::Token(TokenType type, StringType value, const EyeSource& source)
		: m_Type(type), m_Value(value), m_Source(source)
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

	const EyeSource& Token::GetSource() const
	{
		return m_Source;
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
		case TokenType::KeywordDataTypeInt:
		case TokenType::KeywordDataTypeFloat:
		case TokenType::KeywordDataTypeStr:
		case TokenType::KeywordDataTypeBool:
		case TokenType::KeywordTypeQualifierConst:
		case TokenType::KeywordControlIf:
		case TokenType::KeywordControlElse:
		case TokenType::KeywordIterationWhile:
		case TokenType::KeywordIterationDo:
		case TokenType::KeywordIterationFor:
		case TokenType::KeywordIterationContinue:
		case TokenType::KeywordIterationBreak:
		case TokenType::KeywordReturn:
		case TokenType::KeywordFunction:
			type = "Keyword";
			value = TokenTypeStr[(int)m_Type];
			break;
		case TokenType::OperatorBinaryPlus:
		case TokenType::OperatorBinaryMinus:
		case TokenType::OperatorBinaryStar:
		case TokenType::OperatorBinarySlash:
		case TokenType::OperatorBinaryModulo:
		case TokenType::OperatorArithmeticIncrement:
		case TokenType::OperatorArithmeticDecrement:
		case TokenType::OperatorAssignment:
		case TokenType::OperatorAssignmentPlus:
		case TokenType::OperatorAssignmentMinus:
		case TokenType::OperatorAssignmentStar:
		case TokenType::OperatorAssignmentSlash:
		case TokenType::OperatorAssignmentModulo:
		case TokenType::OperatorAssignmentBitwiseAND:
		case TokenType::OperatorAssignmentBitwiseOR:
		case TokenType::OperatorAssignmentBitwiseXOR:
		case TokenType::OperatorAssignmentBitwiseLeftShift:
		case TokenType::OperatorAssignmentBitwiseRightShift:
		case TokenType::OperatorRelationalEquals:
		case TokenType::OperatorRelationalNotEquals:
		case TokenType::OperatorRelationalSmaller:
		case TokenType::OperatorRelationalGreater:
		case TokenType::OperatorRelationalSmallerEquals:
		case TokenType::OperatorRelationalGreaterEquals:
		case TokenType::OperatorLogicalAND:
		case TokenType::OperatorLogicalOR:
		case TokenType::OperatorLogicalNOT:
		case TokenType::OperatorBitwiseBinaryAND:
		case TokenType::OperatorBitwiseBinaryOR:
		case TokenType::OperatorBitwiseBinaryXOR:
		case TokenType::OperatorBitwiseLeftShift:
		case TokenType::OperatorBitwiseRightShift:
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
			value = std::get<StringType>(m_Value);
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

		return "Token{Type: " + type + ", Value: " + value + ", " + m_Source.ToString() + "}";
	}

	std::string_view Token::GetTypeString() const
	{
		return TokenTypeStr[(int)m_Type];
	}

	std::string Token::GetValueString() const
	{
		std::string value = "None";

		switch (m_Type)
		{
		case TokenType::LiteralInteger:
			value = std::to_string(std::get<IntegerType>(m_Value));
			break;
		case TokenType::LiteralFloat:
			value = std::to_string(std::get<FloatType>(m_Value));
			break;
		case TokenType::LiteralString:
			value = std::get<StringType>(m_Value);
			break;
		case TokenType::LiteralBoolean:
			value = (std::get<BooleanType>(m_Value) ? "true" : "false");
			break;
		case TokenType::LiteralNull:
			value = "null";
			break;
		case TokenType::Identifier:
			value = std::get<StringType>(m_Value);
			break;
		case TokenType::KeywordDataTypeInt:
		case TokenType::KeywordDataTypeFloat:
		case TokenType::KeywordDataTypeStr:
		case TokenType::KeywordDataTypeBool:
		case TokenType::KeywordTypeQualifierConst:
		case TokenType::KeywordControlIf:
		case TokenType::KeywordControlElse:
		case TokenType::KeywordIterationWhile:
		case TokenType::KeywordIterationDo:
		case TokenType::KeywordIterationFor:
		case TokenType::KeywordIterationContinue:
		case TokenType::KeywordIterationBreak:
		case TokenType::KeywordReturn:
		case TokenType::KeywordFunction:
			value = TokenTypeStr[(int)m_Type];
			break;
		case TokenType::OperatorBinaryPlus:
		case TokenType::OperatorBinaryMinus:
		case TokenType::OperatorBinaryStar:
		case TokenType::OperatorBinarySlash:
		case TokenType::OperatorBinaryModulo:
		case TokenType::OperatorArithmeticIncrement:
		case TokenType::OperatorArithmeticDecrement:
		case TokenType::OperatorAssignment:
		case TokenType::OperatorAssignmentPlus:
		case TokenType::OperatorAssignmentMinus:
		case TokenType::OperatorAssignmentStar:
		case TokenType::OperatorAssignmentSlash:
		case TokenType::OperatorAssignmentModulo:
		case TokenType::OperatorAssignmentBitwiseAND:
		case TokenType::OperatorAssignmentBitwiseOR:
		case TokenType::OperatorAssignmentBitwiseXOR:
		case TokenType::OperatorAssignmentBitwiseLeftShift:
		case TokenType::OperatorAssignmentBitwiseRightShift:
		case TokenType::OperatorRelationalEquals:
		case TokenType::OperatorRelationalNotEquals:
		case TokenType::OperatorRelationalSmaller:
		case TokenType::OperatorRelationalGreater:
		case TokenType::OperatorRelationalSmallerEquals:
		case TokenType::OperatorRelationalGreaterEquals:
		case TokenType::OperatorLogicalAND:
		case TokenType::OperatorLogicalOR:
		case TokenType::OperatorLogicalNOT:
		case TokenType::OperatorBitwiseBinaryAND:
		case TokenType::OperatorBitwiseBinaryOR:
		case TokenType::OperatorBitwiseBinaryXOR:
		case TokenType::OperatorBitwiseLeftShift:
		case TokenType::OperatorBitwiseRightShift:
		case TokenType::OperatorBitwiseNOT:
		case TokenType::OperatorLeftParenthesis:
		case TokenType::OperatorLeftBracket:
		case TokenType::OperatorQuestionMark:
		case TokenType::OperatorDot:
		case TokenType::OperatorComma:
			value = TokenTypeStr[(int)m_Type];
			break;
		case TokenType::SymbolRightParenthesis:
		case TokenType::SymbolRightBracket:
		case TokenType::SymbolLeftBrace:
		case TokenType::SymbolRightBrace:
		case TokenType::SymbolColon:
		case TokenType::SymbolSemiColon:
		case TokenType::SymbolBackslash:
			value = TokenTypeStr[(int)m_Type];
			break;
		case TokenType::Comment:
			value = std::get<StringType>(m_Value);
			break;
		case TokenType::Newline:
			break;
		case TokenType::EscapeCharacter:
			break;
		case TokenType::EndOfFile:
			break;
		default:
			break;
		}

		return value;
	}
}
