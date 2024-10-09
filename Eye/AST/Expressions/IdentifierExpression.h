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
			IdentifierExpression(const EyeSource& source, std::unique_ptr<Token> identifier)
				: Expression(ExpressionType::IdentifierExpression, source), m_Identifier(std::move(identifier))
			{
			}

			inline std::string GetValue() const { return m_Identifier->GetValue<StringType>(); }

		private:
			std::unique_ptr<Token> m_Identifier;
		};
	}
}
