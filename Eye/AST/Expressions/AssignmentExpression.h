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
			AssignmentExpression(const EyeSource& source, std::unique_ptr<Token> op, std::unique_ptr<Expression> lhsExpression, std::unique_ptr<Expression> expression)
				: Expression(ExpressionType::AssignmentExpression, source), m_Operator(std::move(op)), m_LHSExpression(std::move(lhsExpression)), m_Expression(std::move(expression))
			{
			}

			inline const Token* GetOperator() const { return m_Operator.get(); }
			inline const Expression* GetLHSExpression() const { return m_LHSExpression.get(); }
			inline const Expression* GetExpression() const { return m_Expression.get(); }

		private:
			std::unique_ptr<Token> m_Operator;
			std::unique_ptr<Expression> m_LHSExpression;
			std::unique_ptr<Expression> m_Expression;
		};
	}
}
