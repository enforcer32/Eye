#pragma once

#include "EYEAST/Expressions/Expression.h"
#include "EYEAST/Expressions/IdentifierExpression.h"
#include "EYELexer/Token.h"

#include <memory>

namespace Eye
{
	namespace AST
	{
		/*
			AssignmentExpression
				: AdditiveBinaryExpression
				| IdentifierExpression AssignmentOperator AssignmentExpression
		*/
		class AssignmentExpression : public Expression
		{
		public:
			AssignmentExpression(Lexer::Token op, const std::shared_ptr<IdentifierExpression>& identifier, const std::shared_ptr<Expression>& expression)
				: Expression(ExpressionType::AssignmentExpression), m_Operator(op), m_Identifier(identifier), m_Expression(expression)
			{
			}

			inline Lexer::Token GetOperator() const { return m_Operator; }
			inline std::shared_ptr<IdentifierExpression> GetIdentifier() const { return m_Identifier; }
			inline std::shared_ptr<Expression> GetExpression() const { return m_Expression; }

		private:
			Lexer::Token m_Operator;
			std::shared_ptr<IdentifierExpression> m_Identifier;
			std::shared_ptr<Expression> m_Expression;
		};
	}
}
