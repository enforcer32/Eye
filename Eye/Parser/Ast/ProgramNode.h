#pragma once

#include "Eye/Parser/Ast/StatementNode.h"

#include <vector>
#include <string>
#include <iostream>

namespace EYE
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
	class ProgramNode
	{
	public:
		ProgramNode(std::vector<StatementNode*> statements)
			: m_StatementList(statements)
		{
		}

		std::string ToJSON() const
		{
			std::ostringstream oss;
			oss << "Program {\n";
			oss << "\"type\": \"Program\",\n";
			oss << "\"bodySize\": " << m_StatementList.size() << ",\n";
			oss << "\"body\": [\n";
			for (const auto& stmt : m_StatementList)
			{
				if (stmt->GetType() == StatementNodeType::Expression)
					oss << ((ExpressionStatementNode*)stmt)->ToJSON();
				else if (stmt->GetType() == StatementNodeType::Block)
					oss << ((BlockStatementNode*)stmt)->ToJSON();
			}
			oss << "]\n";
			oss << "}";
			return oss.str();
		}

	private:
		std::vector<StatementNode*> m_StatementList;
	};
}
