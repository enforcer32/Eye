#pragma once

#include "Eye/AST/Statements/Statement.h"

#include <vector>
#include <memory>

namespace Eye
{
	namespace AST
	{
		/*
			Program
				: StatementList
				;

			StatementList
				: Statement
				| StatementList Statement
				;
		*/
		class Program
		{
		public:
			Program(std::vector<std::unique_ptr<Statement>>&& statementList)
				: m_StatementList(std::move(statementList))
			{
			}

			inline const std::vector<std::unique_ptr<Statement>>& GetStatementList() const { return m_StatementList; }

		private:
			std::vector<std::unique_ptr<Statement>> m_StatementList;
		};
	}
}
