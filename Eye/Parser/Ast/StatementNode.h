#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"

namespace EYE
{
	enum class StatementNodeType
	{
		Expression
	};

	class StatementNode
	{
	public:
		virtual ~StatementNode() = default;
		inline StatementNodeType GetType() const { return m_Type; }

	protected:
		StatementNode(StatementNodeType type)
			: m_Type(type)
		{
		}

	private:
		StatementNodeType m_Type;
	};

	class ExpressionStatementNode : public StatementNode
	{
	public:
		ExpressionStatementNode(ExpressionNode* expression)
			: StatementNode(StatementNodeType::Expression), m_Expression(expression)
		{
		}
	private:
		ExpressionNode* m_Expression;
	};
}
