#pragma once

#include "Eye/AST/Expressions/Expression.h"
#include "Eye/AST/Expressions/IdentifierExpression.h"
#include "Eye/Lexer/Token.h"

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
			AssignmentExpression(const EyeSource& source, const std::shared_ptr<Token>& op, const std::shared_ptr<Expression>& lhsExpression, const std::shared_ptr<Expression>& expression)
				: Expression(ExpressionType::AssignmentExpression, source), m_Operator(op), m_LHSExpression(lhsExpression), m_Expression(expression)
			{
			}

			inline std::shared_ptr<Token> GetOperator() const { return m_Operator; }
			inline std::shared_ptr<Expression> GetLHSExpression() const { return m_LHSExpression; }
			inline std::shared_ptr<Expression> GetExpression() const { return m_Expression; }

		private:
			std::shared_ptr<Token> m_Operator;
			std::shared_ptr<Expression> m_LHSExpression;
			std::shared_ptr<Expression> m_Expression;
		};
	}
}
