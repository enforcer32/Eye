#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"
#include "Eye/Parser/Ast/LiteralNode.h"
#include "Eye/Lexer/Token.h"

namespace EYE
{
	/*
		BinaryExpression
			: Expression Operator Expression
			;

	*/
	class BinaryExpressionNode : public ExpressionNode
	{
	public:
		BinaryExpressionNode(ExpressionNode* left, Token op, ExpressionNode* right)
			: ExpressionNode(ExpressionNodeType::Binary), m_Left(left), m_Operator(op), m_Right(right)
		{
		}

		std::string ToJSON() const
		{
			std::ostringstream oss;
			oss << "{\"BinaryExpression\": {\n";
			oss << "\"type\": \"BinaryExpression\",\n";
			if(m_Left->GetType() == ExpressionNodeType::Literal)
				oss << "\"left\": " << ((LiteralNode*)(m_Left))->ToJSON() << ",\n";
			else if(m_Left->GetType() == ExpressionNodeType::Binary)
				oss << "\"left\": " << ((BinaryExpressionNode*)(m_Left))->ToJSON() << ",\n";
			oss << "\"operator\": \"" << m_Operator.String << "\",\n";
			if (m_Right->GetType() == ExpressionNodeType::Literal)
				oss << "\"right\": " << ((LiteralNode*)(m_Right))->ToJSON() << "\n";
			else if (m_Right->GetType() == ExpressionNodeType::Binary)
				oss << "\"right\": " << ((BinaryExpressionNode*)(m_Right))->ToJSON() << "\n";
			oss << "}\n}";
			return oss.str();
		}

	private:
		ExpressionNode* m_Left;
		Token m_Operator;
		ExpressionNode* m_Right;
	};
}
