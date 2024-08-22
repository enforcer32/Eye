#pragma once

#include <string>
#include <variant>
#include <ostream>

namespace Eye
{
	namespace Lexer
	{
		using IntegerType = unsigned long long;
		using FloatType = double;
		using StringType = const char*;
		using BooleanType = bool;

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
			"auto",
			"int",
			"float",
			"str",
			"bool",
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
			"struct",
			"new",
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
			Invalid = 0,
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
			KeywordIf,
			KeywordElse,
			KeywordWhile,
			KeywordDo,
			KeywordFor,
			KeywordContinue,
			KeywordBreak,
			KeywordFunction,
			KeywordReturn,
			KeywordStruct,
			KeywordNew,
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

		class Token
		{
		public:
			Token();
			Token(IntegerType value, Position position);
			Token(FloatType value, Position position);
			Token(StringType value, Position position);
			Token(BooleanType value, Position position);
			Token(TokenType type, Position position);
			Token(TokenType type, StringType value, Position position);

			bool operator==(const Token& token) const;
			bool operator!=(const Token& token) const;
			operator bool() const;

			TokenType GetType() const;

			template<typename T>
			T GetValue() const
			{
				static_assert(std::is_same_v<T, IntegerType> || std::is_same_v<T, FloatType> || std::is_same_v<T, StringType> || std::is_same_v<T, BooleanType>, "EYELexerToken->Error GetValue() Invalid Typename");
				return std::get<T>(m_Value);
			}

			std::string ToString() const;

		private:
			TokenType m_Type;
			Position m_Position;
			std::variant<IntegerType, FloatType, StringType, BooleanType> m_Value;
		};
	}
}
