#pragma once

#include "Eye/Utility/EyeSource.h"

#include <string>
#include <variant>
#include <ostream>

namespace Eye
{
	using IntegerType = unsigned long long;
	using FloatType = double;
	using StringType = std::string;
	using BooleanType = bool;

	enum class TokenType
	{
		Invalid = 0,
		// Literals
		LiteralInteger,
		LiteralFloat,
		LiteralString,
		LiteralBoolean,
		LiteralNull,
		// Identifier & Keyword
		Identifier,
		KeywordDataTypeInt,
		KeywordDataTypeFloat,
		KeywordDataTypeStr,
		KeywordDataTypeBool,
		KeywordDataTypeVoid,
		KeywordTypeQualifierConst,
		KeywordControlIf,
		KeywordControlElse,
		KeywordIterationWhile,
		KeywordIterationDo,
		KeywordIterationFor,
		KeywordIterationContinue,
		KeywordIterationBreak,
		KeywordFunction,
		KeywordReturn,
		// Operators
		OperatorBinaryPlus,
		OperatorBinaryMinus,
		OperatorBinaryStar,
		OperatorBinarySlash,
		OperatorBinaryModulo,
		OperatorArithmeticIncrement,
		OperatorArithmeticDecrement,
		OperatorAssignment,
		OperatorAssignmentPlus,
		OperatorAssignmentMinus,
		OperatorAssignmentStar,
		OperatorAssignmentSlash,
		OperatorAssignmentModulo,
		OperatorAssignmentBitwiseAND,
		OperatorAssignmentBitwiseOR,
		OperatorAssignmentBitwiseXOR,
		OperatorAssignmentBitwiseLeftShift,
		OperatorAssignmentBitwiseRightShift,
		OperatorRelationalEquals,
		OperatorRelationalNotEquals,
		OperatorRelationalSmaller,
		OperatorRelationalGreater,
		OperatorRelationalSmallerEquals,
		OperatorRelationalGreaterEquals,
		OperatorLogicalAND,
		OperatorLogicalOR,
		OperatorLogicalNOT,
		OperatorBitwiseBinaryAND,
		OperatorBitwiseBinaryOR,
		OperatorBitwiseBinaryXOR,
		OperatorBitwiseLeftShift,
		OperatorBitwiseRightShift,
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
	std::string_view TokenTypeToString(TokenType type);
	TokenType StringToTokenType(const std::string& str);

	class Token
	{
	public:
		Token();
		Token(IntegerType value, const EyeSource& source);
		Token(FloatType value, const EyeSource& source);
		Token(StringType value, const EyeSource& source);
		Token(BooleanType value, const EyeSource& source);
		Token(TokenType type, const EyeSource& source);
		Token(TokenType type, StringType value, const EyeSource& source);

		bool operator==(const Token& token) const;
		bool operator!=(const Token& token) const;
		operator bool() const;

		TokenType GetType() const;
		const EyeSource& GetSource() const;

		template<typename T>
		T GetValue() const
		{
			static_assert(std::is_same_v<T, IntegerType> || std::is_same_v<T, FloatType> || std::is_same_v<T, StringType> || std::is_same_v<T, BooleanType>, "EYELexerToken->Error GetValue() Invalid Typename");
			return std::get<T>(m_Value);
		}

		std::string ToString() const;
		std::string_view GetTypeString() const;
		std::string GetValueString() const;

	private:
		TokenType m_Type;
		EyeSource m_Source;
		std::variant<IntegerType, FloatType, StringType, BooleanType> m_Value;
	};
}
