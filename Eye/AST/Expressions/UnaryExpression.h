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
			UnaryExpression(const EyeSource& source, const std::shared_ptr<Token>& op, const std::shared_ptr<Expression>& expression)
				: Expression(ExpressionType::UnaryExpression, source), m_Operator(op), m_Expression(expression)
			{
			}

			inline std::shared_ptr<Token> GetOperator() const { return m_Operator; }
			inline std::shared_ptr<Expression> GetExpression() const { return m_Expression; }

		private:
			std::shared_ptr<Token> m_Operator;
			std::shared_ptr<Expression> m_Expression;
		};
	}
}
