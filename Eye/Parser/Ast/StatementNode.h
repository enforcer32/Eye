#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"
#include "Eye/Parser/Ast/LiteralNode.h"
#include "Eye/Parser/Ast/BinaryExpressionNode.h"
#include "Eye/Parser/Ast/AssignmentExpressionNode.h"
#include "Eye/Parser/Ast/LHSExpressionNode.h"
#include "Eye/Parser/Ast/VariableDeclarationNode.h"

#include <string>
#include <iostream>

namespace EYE
{
	enum class StatementNodeType
	{
		Expression,
		Block,
		Variable
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
		virtual std::string ToJSON() const = 0;
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

		virtual std::string ToJSON() const override
		{
			std::ostringstream oss;
			oss << "{\"ExpressionStatement\": {\n";
			oss << "\"type\": \"ExpressionStatement\",\n";
			oss << "\"expression\": " << m_Expression->ToJSON() << std::endl;			
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

		virtual std::string ToJSON() const override
		{
			std::ostringstream oss;
			oss << "{\"BlockStatement\": {\n";
			oss << "\"type\": \"BlockStatement\",\n";
			oss << "\"bodySize\": " << m_StatementList.size() << ",\n";
			oss << "\"body\": [\n";
			size_t i = 0;
			for (const auto& stmt : m_StatementList)
			{
				oss << "" << stmt->ToJSON();

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


	/*
		VariableStatement
			: 'auto' VariableDeclarationList ';'
			;

		VariableDeclarationList
			: VariableDeclaration
			| VariableDeclarationList ',' VariableDeclaration
			;
	*/
	class VariableStatementNode : public StatementNode
	{
	public:
		VariableStatementNode(const std::vector<VariableDeclarationNode*>& variableDeclarationList)
			: StatementNode(StatementNodeType::Variable), m_VariableDeclarationList(variableDeclarationList)
		{
		}

		virtual std::string ToJSON() const override
		{
			std::ostringstream oss;
			oss << "{\"VariableStatement\": {\n";
			oss << "\"type\": \"VariableStatement\",\n";
			oss << "\"declarationSize\": " << m_VariableDeclarationList.size() << ",\n";
			oss << "\"declarations\": [\n";
			size_t i = 0;
			for (const auto& variable : m_VariableDeclarationList)
			{
				oss << variable->ToJSON();
				i++;
				if ((i + 1) <= m_VariableDeclarationList.size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}";
			return oss.str();
		}

	private:
		std::vector<VariableDeclarationNode*> m_VariableDeclarationList;
	};
}
