#pragma once

#include "EYEAST/Expressions/Expression.h"
#include "EYELexer/Token.h"

namespace Eye
{
	namespace AST
	{
		/*
			PostfixExpression
				: PrimaryExpression
				| PostfixExpression PostfixOperator
				;

			PostfixOperator
				: '++'
				| '--'
				;
		*/
		class PostfixExpression : public Expression
		{
		public:
			PostfixExpression(Lexer::Token op, const std::shared_ptr<Expression>& expression)
				: Expression(ExpressionType::PostfixExpression), m_Operator(op), m_Expression(expression)
			{
			}

			inline Lexer::Token GetOperator() const { return m_Operator; }
			inline std::shared_ptr<Expression> GetExpression() const { return m_Expression; }

		private:
			Lexer::Token m_Operator;
			std::shared_ptr<Expression> m_Expression;
		};
	}
}
