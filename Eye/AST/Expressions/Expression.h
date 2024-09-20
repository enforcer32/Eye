#pragma once

#include "Eye/Utility/EyeSource.h"

namespace Eye
{
	namespace AST
	{
		enum class ExpressionType
		{
			LiteralExpression,
			BinaryExpression,
			UnaryExpression,
			PostfixExpression,
			AssignmentExpression,
			MemberExpression,
			CallExpression,
			IdentifierExpression,
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
			inline const EyeSource& GetSource() const { return m_Source; }

		protected:
			Expression(ExpressionType type, const EyeSource& source)
				: m_Type(type), m_Source(source)
			{
			}

		private:
			ExpressionType m_Type;
			EyeSource m_Source;
		};
	}
}
