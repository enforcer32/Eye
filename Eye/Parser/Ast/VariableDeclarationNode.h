#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"
#include "Eye/Parser/Ast/LiteralNode.h"
#include "Eye/Parser/Ast/BinaryExpressionNode.h"
#include "Eye/Parser/Ast/AssignmentExpressionNode.h"
#include "Eye/Parser/Ast/LHSExpressionNode.h"
#include "Eye/Parser/Ast/Identifier.h"

#include <string>
#include <iostream>

namespace EYE
{
	/*
		VariableDeclaration
			: Identifier OptionalVariableInitializer
			;

		VariableInitializer
			: '=' AssignmentExpression
			;
	*/
	class VariableDeclarationNode
	{
	public:
		VariableDeclarationNode(IdentifierNode* identifier, ExpressionNode* initializer)
			: m_Identifier(identifier), m_Initializer(initializer)
		{
		}

		std::string ToJSON() const
		{
			std::ostringstream oss;
			oss << "{\"VariableDeclaration\": {\n";
			oss << "\"type\": \"VariableDeclaration\",\n";
			oss << "\"identifier\":" << m_Identifier->ToJSON() << ",\n";

			if (m_Initializer)
			{
				if (m_Initializer->GetType() == ExpressionNodeType::Literal) // Virtual ToJSON() for ExpressionNode Class?
					oss << "\"initializer\":" << ((LiteralNode*)m_Initializer)->ToJSON() << "\n";
				else if (m_Initializer->GetType() == ExpressionNodeType::Binary)
					oss << "\"initializer\":" << ((BinaryExpressionNode*)m_Initializer)->ToJSON() << "\n";
				else if (m_Initializer->GetType() == ExpressionNodeType::LHSExpression)
					oss << "\"initializer\":" << ((LHSExpressionNode*)m_Initializer)->ToJSON() << "\n";
				else if (m_Initializer->GetType() == ExpressionNodeType::Assignment)
					oss << "\"initializer\":" << ((AssignmentExpressionNode*)m_Initializer)->ToJSON() << "\n";
			}
			else
			{
				oss << "\"initializer\":" << "null" << "\n";
			}

			oss << "}\n}";
			return oss.str();
		}

	private:
		IdentifierNode* m_Identifier;
		ExpressionNode* m_Initializer;
	};
}
