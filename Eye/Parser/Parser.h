#pragma once

#include "Eye/Common/Eye.h"
#include "Eye/Parser/Node.h"

#include <vector>

namespace EYE
{
	enum class ParserResult
	{
		Successful,
		Failed
	};

	class Parser
	{
	public:
		ParserResult Parse(EyeInstance* eyeInstance);

		// Temporary
		void DebugPrintNodes();

	private:
		Node Program();
		Node Literal();
		Node NumericLiteral();
		Node StringLiteral();
		
		//Node NextNode();

	private:
		Token NextToken();
		Token PeekToken();
		Token EatToken(TokenType type);

		bool HasToken() const;
		bool IsLastToken() const;

	private:
		EyeInstance* m_EyeInstance;
		std::vector<Node> m_Nodes;
		size_t m_CurrentTokenIndex;
		Token m_LookAhead;
	};
}
