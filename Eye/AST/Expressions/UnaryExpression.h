#pragma once

#include "Eye/AST/Expressions/Expression.h"
#include "Eye/Lexer/Token.h"

namespace Eye
{
	namespace AST
	{
		/*
			UnaryExpression
				: LHSExpression
				| UnaryOperator UnaryExpression
				;

			UnaryOperator
				: '+'
				| '-'
				| '!'
				;
		*/
		class UnaryExpression : public Expression
		{
		public:
			UnaryExpression(const EyeSource& source, std::unique_ptr<Token> op, std::unique_ptr<Expression> expression)
				: Expression(ExpressionType::UnaryExpression, source), m_Operator(std::move(op)), m_Expression(std::move(expression))
			{
			}

			inline const Token* GetOperator() const { return m_Operator.get(); }
			inline const Expression* GetExpression() const { return m_Expression.get(); }

		private:
			std::unique_ptr<Token> m_Operator;
			std::unique_ptr<Expression> m_Expression;
		};
	}
}
