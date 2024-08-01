#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"
#include "Eye/Lexer/Token.h"

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
		LHSExpressionNode(Token identifier)
			: ExpressionNode(ExpressionNodeType::LHSExpression), m_Identifier(identifier), m_LHSType(LHSExpressionType::Identifier)
		{
		}

		inline LHSExpressionType GetLHSType() const { return m_LHSType; }

		std::string ToJSON() const
		{
			std::ostringstream oss;
			if (m_LHSType == LHSExpressionType::Identifier)
			{
				oss << "{\"Identifier\": {\n";
				oss << "\"type\": \"Identifier\",\n";
				oss << "\"value\": \"" << m_Identifier.String << "\"\n";
			}
			oss << "}\n}";
			return oss.str();
		}

	private:
		Token m_Identifier;
		LHSExpressionType m_LHSType;
	};
}
