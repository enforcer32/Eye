#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"
#include "Eye/Parser/Ast/Identifier.h"

namespace EYE
{
	/*
		LHSExpression
			: Identifier
			;

		Identifier
			: IDENTIFIER
			;
	*/

	enum class LHSExpressionType
	{
		Identifier,
	};

	class LHSExpressionNode : public ExpressionNode
	{
	public:
		LHSExpressionNode(IdentifierNode* identifier)
			: ExpressionNode(ExpressionNodeType::LHSExpression), m_Identifier(identifier), m_LHSType(LHSExpressionType::Identifier)
		{
		}

		inline LHSExpressionType GetLHSType() const { return m_LHSType; }

		std::string ToJSON() const
		{
			std::ostringstream oss;
			if (m_LHSType == LHSExpressionType::Identifier)
				oss << m_Identifier->ToJSON();
			return oss.str();
		}

	private:
		IdentifierNode* m_Identifier;
		LHSExpressionType m_LHSType;
	};
}
