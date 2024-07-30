#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"
#include "Eye/Parser/Ast/LiteralNode.h"

#include <string>
#include <iostream>

namespace EYE
{
	enum class StatementNodeType
	{
		Expression,
		Block
	};

	/*
		Statement
			: ExpressionStatement
			| BlockStatement
			;
	*/
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

	/*
		ExpressionStatement
			: Expression ';'
			;
	*/
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

	/*
		BlockStatement
			: '{' OptionalStatementList '}'
			;
	*/
	class BlockStatementNode : public StatementNode
	{
	public:
		BlockStatementNode(std::vector<StatementNode*> statements)
			: StatementNode(StatementNodeType::Block), m_StatementList(statements)
		{
		}

		std::string ToString() const
		{
			std::ostringstream oss;
			oss << "\tBlockStatement {\n";
			oss << "\t\t\ttype: BlockStatement\n";
			oss << "\t\t\tbodySize: " << m_StatementList.size() << std::endl;

			oss << "\t\t\tbody: [\n";
			for (const auto& stmt : m_StatementList)
			{
				if (stmt->GetType() == StatementNodeType::Expression)
					oss << "\t\t\t\t" << ((ExpressionStatementNode*)stmt)->ToString();
				else if (stmt->GetType() == StatementNodeType::Block)
					oss << "\t\t\t\t" << ((BlockStatementNode*)stmt)->ToString();
			}
			oss << "\t\t]\n";
			oss << "\t\t}\n";
			return oss.str();
		}

	private:
		std::vector<StatementNode*> m_StatementList;
	};
}
