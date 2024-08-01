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

		virtual std::string ToJSON() const override
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
		ExpressionNode* m_Left;
		Token m_Operator;
		ExpressionNode* m_Right;
	};
}
