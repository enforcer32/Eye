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
#include "Eye/AST/Expressions/CallExpression.h"

#include <expected>
#include <string>

namespace Eye
{
	class Semantic
	{
	public:
		std::expected<bool, Error::Error> Validate(const AST::Program* ast);

	private:
		void ValidateStatement(const AST::Statement* stmt);
		void ValidateExpressionStatement(const AST::ExpressionStatement* exprStmt);
		void ValidateBlockStatement(const AST::BlockStatement* blockStmt, bool createScope = true);
		void ValidateVariableStatement(const AST::VariableStatement* varStmt);
		void ValidateFunctionStatement(const AST::FunctionStatement* functionStmt);
		void ValidateFunctionReturnStatement(const AST::FunctionStatement* functionStmt);
		void ValidateFunctionParameters(const AST::FunctionStatement* functionStmt, const FunctionDeclaration& functionDec);
		void ValidateReturnStatement(const AST::ReturnStatement* returnStmt);

		void ValidateExpression(const AST::Expression* expr);
		void ValidateLiteralExpression(const AST::LiteralExpression* literalExpr);
		void ValidateIdentifierExpression(const AST::IdentifierExpression* identifierExpr);
		void ValidateAssignmentExpression(const AST::AssignmentExpression* assignExpr);
		void ValidateCallExpression(const AST::CallExpression* callExpr);

	private:
		void BeginBlockScope();
		void EndBlockScope();

	private:
		std::shared_ptr<MapEnvironment<DeclarationType>> m_DeclarationEnvironment;
		std::shared_ptr<MapEnvironment<FunctionDeclaration>> m_FunctionDeclarationEnvironment;
		std::shared_ptr<MapEnvironment<VariableTypeQualifier>> m_VariableTypeQualifierEnvironment;
	};
}
