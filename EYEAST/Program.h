#pragma once

#include "EYEAST/Statement.h"

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
			Program(const std::vector<std::shared_ptr<Statement>>& statementList)
				: m_StatementList(statementList)
			{
			}

			inline const std::vector<std::shared_ptr<Statement>>& GetStatementList() const { return m_StatementList; }

		private:
			std::vector<std::shared_ptr<Statement>> m_StatementList;
		};
	}
}
