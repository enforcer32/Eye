#pragma once

#include "EYEAST/Statements/Statement.h"
#include "EYEAST/Expressions/Expression.h"

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
			ExpressionStatement(const Utility::EyeSource& source, const std::shared_ptr<Expression>& expression)
				: Statement(StatementType::ExpressionStatement, source), m_Expression(expression)
			{
			}

			inline std::shared_ptr<Expression> GetExpression() const { return m_Expression; }

		private:
			std::shared_ptr<Expression> m_Expression;
		};
	}
}
