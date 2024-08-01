#pragma once

namespace EYE
{
	enum class ExpressionNodeType
	{
		Literal,
		Binary,
		Assignment,
		LHSExpression
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

		// Virtual ToJSON()?

	private:
		ExpressionNodeType m_Type;
	};
}
