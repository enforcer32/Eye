#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"
#include "Eye/Parser/Ast/LiteralNode.h"

#include <string>
#include <iostream>

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

		std::string ToString() const
		{
			std::ostringstream oss;
			oss << "\tExpressionStatement {\n";
			oss << "\t\t\ttype: ExpressionStatement\n";
			if (m_Expression->GetType() == ExpressionNodeType::Literal)
				oss << "\t\t\texpression: " << ((LiteralNode*)m_Expression)->ToString() << std::endl;
			oss << "\t\t}\n";
			return oss.str();
		}

	private:
		ExpressionNode* m_Expression;
	};
}
