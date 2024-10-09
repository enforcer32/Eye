#pragma once

#include "Eye/TypeChecker/Type.h"
#include "Eye/TypeChecker/Environment.h"
#include "Eye/Error/Error.h"

#include "Eye/AST/Program.h"
#include "Eye/AST/Statements/Statement.h"
#include "Eye/AST/Statements/ExpressionStatement.h"
#include "Eye/AST/Statements/BlockStatement.h"
#include "Eye/AST/Statements/VariableStatement.h"
#include "Eye/AST/Statements/ControlStatement.h"
#include "Eye/AST/Statements/IterationStatement.h"
#include "Eye/AST/Statements/FunctionStatement.h"
#include "Eye/AST/Statements/ReturnStatement.h"

#include "Eye/AST/Expressions/Expression.h"
#include "Eye/AST/Expressions/LiteralExpression.h"
#include "Eye/AST/Expressions/IdentifierExpression.h"
#include "Eye/AST/Expressions/AssignmentExpression.h"
#include "Eye/AST/Expressions/BinaryExpression.h"
#include "Eye/AST/Expressions/CallExpression.h"
#include "Eye/AST/Expressions/UnaryExpression.h"
#include "Eye/AST/Expressions/PostfixExpression.h"

#include <expected>

namespace Eye
{
	class TypeChecker
	{
	public:
		std::expected<bool, Error::Error> TypeCheck(const AST::Program* ast);

	private:
		void TypeCheckStatement(const AST::Statement* stmt);
		void TypeCheckExpressionStatement(const AST::ExpressionStatement* exprStmt);
		void TypeCheckBlockStatement(const AST::BlockStatement* blockStmt, bool createScope = true);
		void TypeCheckVariableStatement(const AST::VariableStatement* varStmt);
		void TypeCheckControlStatement(const AST::ControlStatement* ctrlStmt);
		void TypeCheckIterationStatement(const AST::IterationStatement* iterStmt);
		void TypeCheckWhileStatement(const AST::WhileStatement* whileStmt);
		void TypeCheckDoWhileStatement(const AST::DoWhileStatement* doStmt);
		void TypeCheckForStatement(const AST::ForStatement* forStmt);
		void TypeCheckFunctionStatement(const AST::FunctionStatement* functionStmt);
		void TypeCheckReturnStatement(const AST::ReturnStatement* returnStmt);

		Type TypeCheckExpression(const AST::Expression* expr);
		Type TypeCheckLiteralExpression(const AST::LiteralExpression* literalExpr);
		Type TypeCheckIdentifierExpression(const AST::IdentifierExpression* identifierExpr);
		Type TypeCheckAssignmentExpression(const AST::AssignmentExpression* assignExpr);
		Type TypeCheckAssignmentExpressionAssignment(Type lhsType, Type rightType, const AST::AssignmentExpression* assignExpr);
		Type TypeCheckAssignmentExpressionAssignmentArithmetic(Type lhsType, Type rightType, const AST::AssignmentExpression* assignExpr);
		Type TypeCheckAssignmentExpressionAssignmentBitwsie(Type lhsType, Type rightType, const AST::AssignmentExpression* assignExpr);
		Type TypeCheckBinaryExpression(const AST::BinaryExpression* binaryExpr);
		Type TypeCheckBinaryExpressionArithmetic(Type leftType, Type rightType, const AST::BinaryExpression* binaryExpr);
		Type TypeCheckBinaryExpressionRelational(Type leftType, Type rightType, const AST::BinaryExpression* binaryExpr);
		Type TypeCheckBinaryExpressionLogical(Type leftType, Type rightType, const AST::BinaryExpression* binaryExpr);
		Type TypeCheckBinaryExpressionBitwise(Type leftType, Type rightType, const AST::BinaryExpression* binaryExpr);
		Type TypeCheckCallExpression(const AST::CallExpression* callExpr);
		Type TypeCheckUnaryExpression(const AST::UnaryExpression* unaryExpr);
		Type TypeCheckPostfixExpression(const AST::PostfixExpression* postfixExpr);

	private:
		Type LexerToTypeCheckerType(TokenType type);
		void BeginBlockScope();
		void EndBlockScope();

	private:
		std::shared_ptr<Environment<Type>> m_TypeEnvironment;
		std::shared_ptr<Environment<FunctionType>> m_FunctionEnvironment;
	};
}
