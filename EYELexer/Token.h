#pragma once

#include <EYETypes/Location.h>

#include <string>
#include <variant>
#include <ostream>

namespace Eye
{
	namespace Lexer
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
			Token(IntegerType value, const Types::Location& location);
			Token(FloatType value, const Types::Location& location);
			Token(StringType value, const Types::Location& location);
			Token(BooleanType value, const Types::Location& location);
			Token(TokenType type, const Types::Location& location);
			Token(TokenType type, StringType value, const Types::Location& location);

			bool operator==(const Token& token) const;
			bool operator!=(const Token& token) const;
			operator bool() const;

			TokenType GetType() const;
			const Types::Location& GetLocation() const;

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
			Types::Location m_Location;
			std::variant<IntegerType, FloatType, StringType, BooleanType> m_Value;
		};
	}
}
