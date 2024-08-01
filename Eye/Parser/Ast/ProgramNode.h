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
			oss << "{\"Program\": {\n";
			oss << "\"type\": \"Program\",\n";
			oss << "\"bodySize\": " << m_StatementList.size() << ",\n";
			oss << "\"body\": [\n";
			size_t i = 0;
			for (const auto& stmt : m_StatementList)
			{
				oss << stmt->ToJSON();
				i++;
				if ((i + 1) <= m_StatementList.size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}";
			return oss.str();
		}

	private:
		std::vector<StatementNode*> m_StatementList;
	};
}
