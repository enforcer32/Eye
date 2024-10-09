#pragma once

#include "Eye/AST/Expressions/Expression.h"
#include "Eye/Lexer/Token.h"

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
			BinaryExpression(const EyeSource& source, std::unique_ptr<Token> op, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
				: Expression(ExpressionType::BinaryExpression, source), m_Operator(std::move(op)), m_Left(std::move(left)), m_Right(std::move(right))
			{
			}

			inline const Token* GetOperator() const { return m_Operator.get(); }
			inline const Expression* GetLeft() const { return m_Left.get(); }
			inline const Expression* GetRight() const { return m_Right.get(); }

		private:
			std::unique_ptr<Token> m_Operator;
			std::unique_ptr<Expression> m_Left;
			std::unique_ptr<Expression> m_Right;
		};
	}
}
