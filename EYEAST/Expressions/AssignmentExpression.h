#pragma once

#include "EYEAST/Expressions/Expression.h"
#include "EYEAST/Expressions/IdentifierExpression.h"
#include "EYELexer/Token.h"

#include <memory>

namespace Eye
{
	namespace AST
	{
		/*
			AssignmentExpression
				: LogicalORExpression
				| LHSExpression AssignmentOperator AssignmentExpression
		*/
		class AssignmentExpression : public Expression
		{
		public:
			AssignmentExpression(Lexer::Token op, const std::shared_ptr<Expression>& lhsExpression, const std::shared_ptr<Expression>& expression)
				: Expression(ExpressionType::AssignmentExpression), m_Operator(op), m_LHSExpression(lhsExpression), m_Expression(expression)
			{
			}

			inline Lexer::Token GetOperator() const { return m_Operator; }
			inline std::shared_ptr<Expression> GetLHSExpression() const { return m_LHSExpression; }
			inline std::shared_ptr<Expression> GetExpression() const { return m_Expression; }

		private:
			Lexer::Token m_Operator;
			std::shared_ptr<Expression> m_LHSExpression;
			std::shared_ptr<Expression> m_Expression;
		};
	}
}
