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
			CallExpression(const EyeSource& source, std::unique_ptr<Expression> callee, const std::vector<std::unique_ptr<Expression>>& arguments)
				: Expression(ExpressionType::CallExpression, source), m_Callee(std::move(callee)), m_Arguments(arguments)
			{
			}

			inline const Expression* GetCallee() const { return m_Callee.get(); }
			inline const std::vector<std::unique_ptr<Expression>>& GetArguments() const { return m_Arguments; }

		private:
			std::unique_ptr<Expression> m_Callee;
			std::vector<std::unique_ptr<Expression>> m_Arguments;
		};
	}
}
