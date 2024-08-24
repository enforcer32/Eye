#pragma once

namespace Eye
{
	namespace AST
	{
		enum class ExpressionType
		{
			LiteralExpression,
			BinaryExpression,
			UnaryExpression,
			AssignmentExpression,
			MemberExpression,
			FunctionCallExpression,
			NewExpression,
			IdentifierExpression, // RHS?
		};

		/*
			Expression
				: PrimaryExpression
				;
		*/
		class Expression
		{
		public:
			inline ExpressionType GetType() const { return m_Type; }

		protected:
			Expression(ExpressionType type)
				: m_Type(type)
			{
			}

		private:
			ExpressionType m_Type;
		};
	}
}
