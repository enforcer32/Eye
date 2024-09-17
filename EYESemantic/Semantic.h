#pragma once

#include "EYESemantic/Environment.h"

#include <EYEError/Error.h>

#include <EYEAST/Program.h>
#include <EYEAST/Statements/Statement.h>
#include <EYEAST/Statements/ExpressionStatement.h>

#include <EYEAST/Expressions/Expression.h>
#include <EYEAST/Expressions/IdentifierExpression.h>

#include <expected>
#include <string>

namespace Eye
{
	namespace Semantic
	{
		class Semantic
		{
		public:
			std::expected<bool, Error::Error> Validate(const std::shared_ptr<AST::Program>& ast);

		private:
			void ValidateStatement(const std::shared_ptr<AST::Statement>& stmt);
			void ValidateExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt);
				
			void ValidateExpression(const std::shared_ptr<AST::Expression>& expr);
			void ValidateIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr);

		private:
			std::shared_ptr<Environment<std::string>> m_VariableEnvironment;
		};
	}
}
