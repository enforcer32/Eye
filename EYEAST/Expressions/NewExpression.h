#pragma once

#include "EYEAST/Expressions/Expression.h"

#include <memory>

namespace Eye
{
	namespace AST
	{
		/*
			NewExpression
				: 'new' MemberExpression
				;
		*/
		class NewExpression : public Expression
		{
		public:
			NewExpression(const std::shared_ptr<Expression>& callee)
				: Expression(ExpressionType::NewExpression), m_Callee(callee)
			{
			}

			inline std::shared_ptr<Expression> GetCallee() const { return m_Callee; }

		private:
			std::shared_ptr<Expression> m_Callee;
		};
	}
}
