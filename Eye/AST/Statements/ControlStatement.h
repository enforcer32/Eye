#pragma once

#include "Eye/AST/Statements/Statement.h"
#include "Eye/AST/Expressions/Expression.h"

#include <memory>

namespace Eye
{
	namespace AST
	{
		/*
			ControlStatement
				: 'if' '(' Expression ')' Statement
				| 'if' '(' Expression ')' Statement 'else' Statement
				;
		*/
		class ControlStatement : public Statement
		{
		public:
			ControlStatement(const EyeSource& source, std::unique_ptr<Expression> condition, std::unique_ptr<Statement> consequent, std::unique_ptr<Statement> alternate)
				: Statement(StatementType::ControlStatement, source), m_Condition(std::move(condition)), m_Consequent(std::move(consequent)), m_Alternate(std::move(alternate))
			{
			}
		
			inline const Expression* GetCondition() const { return m_Condition.get(); }
			inline const Statement* GetConsequent() const { return m_Consequent.get(); }
			inline const Statement* GetAlternate() const { return m_Alternate.get(); }

		private:
			std::unique_ptr<Expression> m_Condition;
			std::unique_ptr<Statement> m_Consequent;
			std::unique_ptr<Statement> m_Alternate;
		};
	}
}
