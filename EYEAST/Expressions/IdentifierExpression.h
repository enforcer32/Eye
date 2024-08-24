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
			IdentifierExpression(Lexer::Token identifier)
				: Expression(ExpressionType::IdentifierExpression), m_Identifier(identifier)
			{
			}

			inline std::string GetValue() const { return m_Identifier.GetValue<Lexer::StringType>(); }

		private:
			Lexer::Token m_Identifier;
		};
	}
}
