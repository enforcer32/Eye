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

		std::string ToString() const
		{
			std::ostringstream oss;
			oss << "Program {\n";
			oss << "\ttype: Program\n";
			oss << "\tbodySize: " << m_StatementList.size() << std::endl;
			oss << "\tbody: [\n";
			for (const auto& stmt : m_StatementList)
			{
				if (stmt->GetType() == StatementNodeType::Expression)
					oss << "\t" << ((ExpressionStatementNode*)stmt)->ToString();
				else if (stmt->GetType() == StatementNodeType::Block)
					oss << "\t" << ((BlockStatementNode*)stmt)->ToString();
			}
			oss << "\t]\n";
			oss << "}";
			return oss.str();
		}

	private:
		std::vector<StatementNode*> m_StatementList;
	};
}
