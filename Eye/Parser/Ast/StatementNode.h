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

		std::string ToJSON() const
		{
			std::ostringstream oss;
			oss << "{\"ExpressionStatement\": {\n";
			oss << "\"type\": \"ExpressionStatement\",\n";
			if (m_Expression->GetType() == ExpressionNodeType::Literal)
				oss << "\"expression\": " << ((LiteralNode*)m_Expression)->ToJSON() << std::endl;
			oss << "}\n}\n";
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

		std::string ToJSON() const
		{
			std::ostringstream oss;
			oss << "{\"BlockStatement\": {\n";
			oss << "\"type\": \"BlockStatement\",\n";
			oss << "\"bodySize\": " << m_StatementList.size() << ",\n";

			oss << "\"body\": [\n";
			size_t i = 0;
			for (const auto& stmt : m_StatementList)
			{
				if (stmt->GetType() == StatementNodeType::Expression)
					oss << "" << ((ExpressionStatementNode*)stmt)->ToJSON();
				else if (stmt->GetType() == StatementNodeType::Block)
					oss << "" << ((BlockStatementNode*)stmt)->ToJSON();

				i++;
				if ((i + 1) <= m_StatementList.size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}\n";
			return oss.str();
		}

	private:
		std::vector<StatementNode*> m_StatementList;
	};
}
