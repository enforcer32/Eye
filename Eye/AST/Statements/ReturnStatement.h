#pragma once

#include "Eye/AST/Statements/Statement.h"
#include "Eye/AST/Expressions/Expression.h"

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
			ReturnStatement(const EyeSource& source, const std::shared_ptr<Expression>& expression)
				: Statement(StatementType::ReturnStatement, source), m_Expression(expression)
			{
			}

			inline std::shared_ptr<Expression> GetExpression() const { return m_Expression; }

		private:
			std::shared_ptr<Expression> m_Expression;
		};
	}
}
