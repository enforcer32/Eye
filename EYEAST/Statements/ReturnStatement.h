#pragma once

#include "EYEAST/Statements/Statement.h"
#include "EYEAST/Expressions/Expression.h"

#include <memory>

namespace Eye
{
	namespace AST
	{
		/*
			ReturnStatement
				: 'return' OptionalExpression ';'
				;
		*/
		class ReturnStatement : public Statement
		{
		public:
			ReturnStatement(const std::shared_ptr<Expression>& expression, const Types::Location& source)
				: Statement(StatementType::ReturnStatement, source), m_Expression(expression)
			{
			}

			inline std::shared_ptr<Expression> GetExpression() const { return m_Expression; }

		private:
			std::shared_ptr<Expression> m_Expression;
		};
	}
}
