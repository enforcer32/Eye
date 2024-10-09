#pragma once

#include "Eye/AST/Statements/Statement.h"
#include "Eye/AST/Expressions/Expression.h"

namespace Eye
{
	namespace AST
	{
		/*
			ExpressionStatement
				: Expression ';'
				;
		*/
		class ExpressionStatement : public Statement
		{
		public:
			ExpressionStatement(const EyeSource& source, std::unique_ptr<Expression> expression)
				: Statement(StatementType::ExpressionStatement, source), m_Expression(std::move(expression))
			{
			}

			inline const Expression* GetExpression() const { return m_Expression.get(); }

		private:
			std::unique_ptr<Expression> m_Expression;
		};
	}
}
