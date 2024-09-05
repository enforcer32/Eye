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
			AssignmentExpression(const std::shared_ptr<Lexer::Token>& op, const std::shared_ptr<Expression>& lhsExpression, const std::shared_ptr<Expression>& expression, const Types::Location& source)
				: Expression(ExpressionType::AssignmentExpression, source), m_Operator(op), m_LHSExpression(lhsExpression), m_Expression(expression)
			{
			}

			inline std::shared_ptr<Lexer::Token> GetOperator() const { return m_Operator; }
			inline std::shared_ptr<Expression> GetLHSExpression() const { return m_LHSExpression; }
			inline std::shared_ptr<Expression> GetExpression() const { return m_Expression; }

		private:
			std::shared_ptr<Lexer::Token> m_Operator;
			std::shared_ptr<Expression> m_LHSExpression;
			std::shared_ptr<Expression> m_Expression;
		};
	}
}
