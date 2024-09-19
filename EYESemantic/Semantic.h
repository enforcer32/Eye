#pragma once

#include "EYESemantic/SetEnvironment.h"
#include "EYESemantic/MapEnvironment.h"
#include "EYESemantic/Types.h"

#include <EYEError/Error.h>

#include <EYEAST/Program.h>
#include <EYEAST/Statements/Statement.h>
#include <EYEAST/Statements/ExpressionStatement.h>
#include <EYEAST/Statements/BlockStatement.h>
#include <EYEAST/Statements/VariableStatement.h>

#include <EYEAST/Expressions/Expression.h>
#include <EYEAST/Expressions/LiteralExpression.h>
#include <EYEAST/Expressions/IdentifierExpression.h>
#include <EYEAST/Expressions/AssignmentExpression.h>

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
			void ValidateBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt, bool createScope = true);
			void ValidateVariableStatement(const std::shared_ptr<AST::VariableStatement>& varStmt);

			void ValidateExpression(const std::shared_ptr<AST::Expression>& expr);
			void ValidateLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr);
			void ValidateIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr);
			void ValidateAssignmentExpression(const std::shared_ptr<AST::AssignmentExpression>& assignExpr);

		private:
			void BeginBlockScope();
			void EndBlockScope();

		private:
			std::shared_ptr<SetEnvironment<std::string>> m_VariableEnvironment;
			std::shared_ptr<MapEnvironment<VariableTypeQualifier>> m_VariableTypeQualifierEnvironment;
		};
	}
}
