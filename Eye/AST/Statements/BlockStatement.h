#pragma once

#include "Eye/AST/Statements/Statement.h"

#include <memory>
#include <vector>

namespace Eye
{
	namespace AST
	{
		/*
			BlockStatement
				: '{' OptionalStatementList '}'
				;
		*/
		class BlockStatement : public Statement
		{
		public:
			BlockStatement(const EyeSource& source, const std::vector<std::shared_ptr<Statement>>& statementList)
				: Statement(StatementType::BlockStatement, source), m_StatementList(statementList)
			{
			}

			inline const std::vector<std::shared_ptr<Statement>>& GetStatementList() const { return m_StatementList; }

		private:
			std::vector<std::shared_ptr<Statement>> m_StatementList;
		};
	}
}
