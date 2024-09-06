#pragma once

#include "EYEAST/Expressions/Expression.h"
#include "EYELexer/Token.h"

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
			IdentifierExpression(const Utility::EyeSource& source, const std::shared_ptr<Lexer::Token>& identifier)
				: Expression(ExpressionType::IdentifierExpression, source), m_Identifier(identifier)
			{
			}

			inline std::string GetValue() const { return m_Identifier->GetValue<Lexer::StringType>(); }

		private:
			std::shared_ptr<Lexer::Token> m_Identifier;
		};
	}
}
