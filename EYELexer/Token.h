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

		class Token
		{
		public:
			Token();
			Token(Integer value, Position position);
			Token(Float value, Position position);
			Token(String value, Position position);
			Token(Boolean value, Position position);
			Token(TokenType type, Position position);
			Token(TokenType type, String value, Position position);

			bool operator==(const Token& token) const;
			bool operator!=(const Token& token) const;
			operator bool() const;

			TokenType GetType() const;

			template<typename T>
			T GetValue() const
			{
				static_assert(std::is_same_v<T, Integer> || std::is_same_v<T, Float> || std::is_same_v<T, String> || std::is_same_v<T, Boolean>, "EYELexerToken->Error GetValue() Invalid Typename");
				return std::get<T>(m_Value);
			}

			std::string ToString() const;

		private:
			TokenType m_Type;
			Position m_Position;
			std::variant<Integer, Float, String, Boolean> m_Value;
		};
	}
}
