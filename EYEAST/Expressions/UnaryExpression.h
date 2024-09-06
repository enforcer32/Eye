#pragma once

#include "EYEAST/Expressions/Expression.h"
#include "EYELexer/Token.h"

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
			UnaryExpression(const Utility::EyeSource& source, const std::shared_ptr<Lexer::Token>& op, const std::shared_ptr<Expression>& expression)
				: Expression(ExpressionType::UnaryExpression, source), m_Operator(op), m_Expression(expression)
			{
			}

			inline std::shared_ptr<Lexer::Token> GetOperator() const { return m_Operator; }
			inline std::shared_ptr<Expression> GetExpression() const { return m_Expression; }

		private:
			std::shared_ptr<Lexer::Token> m_Operator;
			std::shared_ptr<Expression> m_Expression;
		};
	}
}
