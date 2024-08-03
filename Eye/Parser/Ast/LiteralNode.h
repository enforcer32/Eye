#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"

namespace EYE
{
	enum class LiteralNodeType
	{
		Number,
		String,
		Boolean,
		Null
	};

	/*
		Literal
			: NumericLiteral
			| StringLiteral
			| BooleanLiteral
			| NullLiteral
			;

		NumericLiteral
			: NUMBER
			;

		StringLiteral
			: STRING
			;

		BooleanLiteral
			: BOOL
			;

		NullLiteral
			: NULL
			;
	*/
	class LiteralNode : public ExpressionNode
	{
	public:
		LiteralNode(LiteralNodeType type, void* data)
			: ExpressionNode(ExpressionNodeType::Literal), m_Type(type), m_Any(data)
		{
		}

		virtual std::string ToJSON() const override
		{
			std::ostringstream oss;
			oss << "{\"Literal\": {\n";
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
			else if (m_Type == LiteralNodeType::Boolean)
			{
				oss << "\"type\": \"Boolean\",\n";
				oss << "\"value\": " << (m_Boolean ? "true" : "false") << "\n";
			}
			else if (m_Type == LiteralNodeType::Null)
			{
				oss << "\"type\": \"Null\",\n";
				oss << "\"value\": null\n";
			}
			oss << "}\n}";
			return oss.str();
		}

	private:
		LiteralNodeType m_Type; // BUG (m_Type also defined in Superclass)
		union
		{
			unsigned long long m_Number;
			const char* m_String;
			bool m_Boolean;
			void* m_Any;
		};
	};
}
