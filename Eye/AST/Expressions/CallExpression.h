#pragma once

#include "Eye/AST/Expressions/Expression.h"
#include "Eye/Lexer/Token.h"

#include <memory>
#include <vector>

namespace Eye
{
	namespace AST
	{
		/*
			CallExpression
				: Callee CallArguments
				;

			Callee
				: MemberExpression
				| CallExpression
				;

			CallArguments
				: '(' OptionalCallArgumentList ')'
				;

			CallArgumentList
				: AssignmentExpression
				| CallArgumentList ',' AssignmentExpression
				;
		*/
		class CallExpression : public Expression
		{
		public:
			CallExpression(const EyeSource& source, const std::shared_ptr<Expression>& callee, const std::vector<std::shared_ptr<Expression>>& arguments)
				: Expression(ExpressionType::CallExpression, source), m_Callee(callee), m_Arguments(arguments)
			{
			}

			inline std::shared_ptr<Expression> GetCallee() const { return m_Callee; }
			inline const std::vector<std::shared_ptr<Expression>>& GetArguments() const { return m_Arguments; }

		private:
			std::shared_ptr<Expression> m_Callee;
			std::vector<std::shared_ptr<Expression>> m_Arguments;
		};
	}
}
