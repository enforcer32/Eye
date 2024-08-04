#pragma once

namespace EYE
{
	enum class ExpressionNodeType
	{
		Literal,
		Binary,
		Unary,
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
		virtual std::string ToJSON() const = 0;
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
