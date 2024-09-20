#pragma once

#include "Eye/AST/Expressions/Expression.h"
#include "Eye/Lexer/Token.h"

namespace Eye
{
	namespace AST
	{
		/*
			IdentifierExpression
				: IdentifierToken
				;
		*/
		class IdentifierExpression : public Expression
		{
		public:
			IdentifierExpression(const EyeSource& source, const std::shared_ptr<Token>& identifier)
				: Expression(ExpressionType::IdentifierExpression, source), m_Identifier(identifier)
			{
			}

			inline std::string GetValue() const { return m_Identifier->GetValue<StringType>(); }

		private:
			std::shared_ptr<Token> m_Identifier;
		};
	}
}
