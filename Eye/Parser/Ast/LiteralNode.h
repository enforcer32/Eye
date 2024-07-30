#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"

namespace EYE
{
	enum class LiteralNodeType
	{
		Number,
		String
	};

	/*
		Literal
			: NumericLiteral
			| StringLiteral
			;

		NumericLiteral
			: NUMBER
			;

		StringLiteral
			: STRING
			;
	*/
	class LiteralNode : public ExpressionNode
	{
	public:
		LiteralNode(LiteralNodeType type, void* data)
			: ExpressionNode(ExpressionNodeType::Literal), m_Type(type), m_Any(data)
		{
		}

		std::string ToJSON() const
		{
			std::ostringstream oss;
			oss << "Literal {\n";
			if (m_Type == LiteralNodeType::Number)
			{
				oss << "\"type\": \"Number\",\n";
				oss << "\"value\": " << m_Number << "\n";
			}
			else if (m_Type == LiteralNodeType::String)
			{
				oss << "\"type\": \"String\",\n";
				oss << "\"value\": " << "\"" << m_String << "\"\n";
			}
			oss << "}";
			return oss.str();
		}

	private:
		LiteralNodeType m_Type;
		union
		{
			unsigned long long m_Number;
			const char* m_String;
			void* m_Any;
		};
	};
}
