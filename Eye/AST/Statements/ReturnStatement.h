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
			ReturnStatement(const EyeSource& source, std::unique_ptr<Expression> expression)
				: Statement(StatementType::ReturnStatement, source), m_Expression(std::move(expression))
			{
			}

			inline const Expression* GetExpression() const { return m_Expression.get(); }

		private:
			std::unique_ptr<Expression> m_Expression;
		};
	}
}
