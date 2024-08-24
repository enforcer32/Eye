#pragma once

#include "EYEAST/Expressions/Expression.h"
#include "EYELexer/Token.h"

#include <memory>

namespace Eye
{
	namespace AST
	{
		/*
			BinaryExpression
				: Expression Operator Expression
				;
		*/
		class BinaryExpression : public Expression
		{
		public:
			BinaryExpression(Lexer::Token op, const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right)
				: Expression(ExpressionType::BinaryExpression), m_Operator(op), m_Left(left), m_Right(right)
			{
			}

			inline Lexer::Token GetOperator() const { return m_Operator; }
			inline std::shared_ptr<Expression> GetLeft() const { return m_Left; }
			inline std::shared_ptr<Expression> GetRight() const { return m_Right; }

		private:
			Lexer::Token m_Operator;
			std::shared_ptr<Expression> m_Left;
			std::shared_ptr<Expression> m_Right;
		};
	}
}
