#pragma once

namespace EYE
{
	enum class ExpressionNodeType
	{
		Literal,
		Binary
	};

	/*
		Expression
			: Literal
			;
	*/
	class ExpressionNode
	{
	public:
		virtual ~ExpressionNode() = default;
		inline ExpressionNodeType GetType() const { return m_Type; }

	protected:
		ExpressionNode(ExpressionNodeType type)
			: m_Type(type)
		{
		}

	private:
		ExpressionNodeType m_Type;
	};
}
