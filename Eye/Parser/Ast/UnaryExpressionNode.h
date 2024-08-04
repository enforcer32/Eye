#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"
#include "Eye/Parser/Ast/LiteralNode.h"
#include "Eye/Lexer/Token.h"

#include <sstream>

namespace EYE
{
	/*
		UnaryExpression
			: UnaryOperator Expression
			;

		UnaryOperator
			: '!'
			| '-'
			;

	*/
	class UnaryExpressionNode : public ExpressionNode
	{
	public:
		UnaryExpressionNode(Token op, ExpressionNode* expr)
			: ExpressionNode(ExpressionNodeType::Unary), m_Operator(op), m_Expr(expr)
		{
		}

		virtual std::string ToJSON() const override
		{
			std::ostringstream oss;
			oss << "{\"UnaryExpression\": {\n";
			oss << "\"type\": \"UnaryExpression\",\n";
			oss << "\"operator\": \"" << m_Operator.String << "\",\n";
			oss << "\"expr\": " << m_Expr->ToJSON() << "\n";
			oss << "}\n}";
			return oss.str();
		}

	private:
		Token m_Operator;
		ExpressionNode* m_Expr;
	};
}
