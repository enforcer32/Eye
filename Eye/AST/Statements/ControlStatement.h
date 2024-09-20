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
			ControlStatement(const EyeSource& source, const std::shared_ptr<Expression>& condition, const std::shared_ptr<Statement>& consequent, const std::shared_ptr<Statement>& alternate)
				: Statement(StatementType::ControlStatement, source), m_Condition(condition), m_Consequent(consequent), m_Alternate(alternate)
			{
			}
		
			inline std::shared_ptr<Expression> GetCondition() const { return m_Condition; }
			inline std::shared_ptr<Statement> GetConsequent() const { return m_Consequent; }
			inline std::shared_ptr<Statement> GetAlternate() const { return m_Alternate; }

		private:
			std::shared_ptr<Expression> m_Condition;
			std::shared_ptr<Statement> m_Consequent;
			std::shared_ptr<Statement> m_Alternate;
		};
	}
}
