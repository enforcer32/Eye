#pragma once

#include "EYEAST/Statements/Statement.h"
#include "EYEAST/Statements/VariableStatement.h"
#include "EYEAST/Expressions/IdentifierExpression.h"

#include <memory>
#include <vector>

namespace Eye
{
	namespace AST
	{
		/*
			StructStatement
				: 'struct' Identifier '{' OptionalVariableStatementList '}' ';'
				;
		*/
		class StructStatement : public Statement
		{
		public:
			StructStatement(const std::shared_ptr<IdentifierExpression>& identifier, const std::vector<std::shared_ptr<VariableStatement>>& members)
				: Statement(StatementType::StructStatement), m_Identifier(identifier), m_Members(members)
			{
			}

			inline std::shared_ptr<IdentifierExpression> GetIdentifier() const { return m_Identifier; }
			inline const std::vector<std::shared_ptr<VariableStatement>>& GetMembers() const { return m_Members; }

		private:
			std::shared_ptr<IdentifierExpression> m_Identifier;
			std::vector<std::shared_ptr<VariableStatement>> m_Members;
		};
	}
}
