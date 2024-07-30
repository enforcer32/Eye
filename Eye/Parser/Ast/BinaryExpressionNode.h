#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"
#include "Eye/Parser/Ast/LiteralNode.h"
#include "Eye/Lexer/Token.h"

namespace EYE
{
	/*
		BinaryExpression
			: Literal Operator Literal
			;

	*/
	class BinaryExpressionNode : public ExpressionNode
	{
	public:
		BinaryExpressionNode(LiteralNode* left, Token op, LiteralNode* right)
			: ExpressionNode(ExpressionNodeType::Binary), m_Left(left), m_Operator(op), m_Right(right)
		{
		}

		std::string ToJSON() const
		{
			std::ostringstream oss;
			oss << "{\"BinaryExpression\": {\n";
			oss << "\"type\": \"BinaryExpression\",\n";
			oss << "\"left\": " << m_Left->ToJSON() << ",\n";
			oss << "\"operator\": \"" << m_Operator.String << "\",\n";
			oss << "\"right\": " << m_Right->ToJSON() << "\n";
			oss << "}\n}";
			return oss.str();
		}

	private:
		LiteralNode* m_Left;
		Token m_Operator;
		LiteralNode* m_Right;
	};
}
