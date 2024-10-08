#pragma once

#include "Eye/AST/Expressions/Expression.h"

#include <string>
#include <variant>

namespace Eye
{
	namespace AST
	{
		using LiteralIntegerType = unsigned long long;
		using LiteralFloatType = double;
		using LiteralStringType = std::string;
		using LiteralBooleanType = bool;

		enum class LiteralType
		{
			Integer,
			Float,
			String,
			Boolean,
			Null
		};

		/*
			LiteralExpression
				: IntegerLiteral
				| FloatLtieral
				| StringLiteral
				| BooleanLiteral
				| NullLiteral
				;

			IntegerLiteral
				: INTEGER
				;

			FloatLiteral
				: FLOAT
				;

			StringLiteral
				: STRING
				;

			BooleanLiteral
				: BOOL
				;

			NullLiteral
				: NULL
				;
		*/
		class LiteralExpression : public Expression
		{
		public:
			LiteralExpression(const EyeSource& source, LiteralType type)
				: Expression(ExpressionType::LiteralExpression, source), m_LiteralType(type)
			{
			}

			LiteralExpression(const EyeSource& source, LiteralIntegerType value)
				: Expression(ExpressionType::LiteralExpression, source), m_LiteralType(LiteralType::Integer), m_Value(value)
			{
			}

			LiteralExpression(const EyeSource& source, LiteralFloatType value)
				: Expression(ExpressionType::LiteralExpression, source), m_LiteralType(LiteralType::Float), m_Value(value)
			{
			}

			LiteralExpression(const EyeSource& source, LiteralStringType value)
				: Expression(ExpressionType::LiteralExpression, source), m_LiteralType(LiteralType::String), m_Value(value)
			{
			}

			LiteralExpression(const EyeSource& source, LiteralBooleanType value)
				: Expression(ExpressionType::LiteralExpression, source), m_LiteralType(LiteralType::Boolean), m_Value(value)
			{
			}

			inline LiteralType GetLiteralType() const { return m_LiteralType; }

			template<typename T>
			T GetValue() const
			{
				static_assert(std::is_same_v<T, LiteralIntegerType> || std::is_same_v<T, LiteralFloatType> || std::is_same_v<T, LiteralStringType> || std::is_same_v<T, LiteralBooleanType>, "EYELiteralExpression->Error GetValue() Invalid Typename");
				return std::get<T>(m_Value);
			}

		private:
			LiteralType m_LiteralType;
			std::variant<LiteralIntegerType, LiteralFloatType, LiteralStringType, LiteralBooleanType> m_Value;
		};
	}
}
