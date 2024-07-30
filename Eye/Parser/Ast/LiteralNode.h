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
