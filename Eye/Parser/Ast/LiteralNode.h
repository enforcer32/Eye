#pragma once

#include "Eye/Parser/Ast/ExpressionNode.h"

namespace EYE
{
	enum class LiteralNodeType
	{
		Number,
		String
	};

	class LiteralNode : public ExpressionNode
	{
	public:
		LiteralNode(LiteralNodeType type, void* data)
			: ExpressionNode(ExpressionNodeType::Literal), m_Type(type), m_Any(data)
		{
		}

		std::string ToString() const
		{
			std::ostringstream oss;
			oss << "Literal {\n";
			if (m_Type == LiteralNodeType::Number)
			{
				oss << "\t\t\t\ttype: Number\n";
				oss << "\t\t\t\tvalue: " << m_Number << std::endl;
			}
			else if (m_Type == LiteralNodeType::String)
			{
				oss << "\t\t\t\ttype: String\n";
				oss << "\t\t\t\tvalue: " << m_String << std::endl;
			}
			oss << "\t\t\t}\n";
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
