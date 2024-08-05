#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"
#include "Eye/Parser/Ast/LHSExpressionNode.h"
#include "Eye/Lexer/Token.h"

namespace EYE
{
	/*
		AssignmentExpression
			: LogicalORExpression
			| LHSExpression AssignmentOperator AssignmentExpression
			;
	*/
	class AssignmentExpressionNode : public ExpressionNode
	{
	public:
		AssignmentExpressionNode(LHSExpressionNode* left, Token op, ExpressionNode* right)
			: ExpressionNode(ExpressionNodeType::Assignment), m_Left(left), m_Operator(op), m_Right(right)
		{
		}

		virtual std::string ToJSON() const override
		{
			std::ostringstream oss;
			oss << "{\"AssignmentExpression\": {\n";
			oss << "\"type\": \"AssignmentExpression\",\n";
			oss << "\"left\": " << m_Left->ToJSON() << ",\n";
			oss << "\"operator\": \"" << m_Operator.String << "\",\n";
			oss << "\"right\": " << m_Right->ToJSON() << "\n";
			oss << "}\n}";
			return oss.str();
		}

	private:
		LHSExpressionNode* m_Left;
		Token m_Operator;
		ExpressionNode* m_Right;
	};
}
