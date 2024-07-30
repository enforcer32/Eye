#pragma once

#include "Eye/Parser/Ast/StatementNode.h"

#include <vector>

namespace EYE
{
	class ProgramNode
	{
	public:
		ProgramNode(std::vector<StatementNode*> statements)
			: m_StatementList(statements)
		{
		}

	private:
		std::vector<StatementNode*> m_StatementList;
	};
}
