#pragma once

#include "Eye/Semantic/MapEnvironment.h"
#include "Eye/Semantic/Types.h"
#include "Eye/Error/Error.h"

#include "Eye/AST/Program.h"
#include "Eye/AST/Statements/Statement.h"
#include "Eye/AST/Statements/ExpressionStatement.h"
#include "Eye/AST/Statements/BlockStatement.h"
#include "Eye/AST/Statements/VariableStatement.h"
#include "Eye/AST/Statements/FunctionStatement.h"
#include "Eye/AST/Statements/ReturnStatement.h"

#include "Eye/AST/Expressions/Expression.h"
#include "Eye/AST/Expressions/LiteralExpression.h"
#include "Eye/AST/Expressions/IdentifierExpression.h"
#include "Eye/AST/Expressions/AssignmentExpression.h"

#include <expected>
#include <string>

namespace Eye
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
		void ValidateFunctionStatement(const std::shared_ptr<AST::FunctionStatement>& functionStmt);
		void ValidateFunctionReturnStatement(const std::shared_ptr<AST::FunctionStatement>& functionStmt);
		void ValidateReturnStatement(const std::shared_ptr<AST::ReturnStatement>& returnStmt);

		void ValidateExpression(const std::shared_ptr<AST::Expression>& expr);
		void ValidateLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr);
		void ValidateIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr);
		void ValidateAssignmentExpression(const std::shared_ptr<AST::AssignmentExpression>& assignExpr);

	private:
		void BeginBlockScope();
		void EndBlockScope();

	private:
		std::shared_ptr<MapEnvironment<DeclarationType>> m_DeclarationEnvironment;
		std::shared_ptr<MapEnvironment<VariableTypeQualifier>> m_VariableTypeQualifierEnvironment;
	};
}
