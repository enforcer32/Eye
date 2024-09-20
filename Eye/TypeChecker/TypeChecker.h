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
		std::expected<bool, Error::Error> TypeCheck(const std::shared_ptr<AST::Program>& ast);

	private:
		void TypeCheckStatement(const std::shared_ptr<AST::Statement>& stmt);
		void TypeCheckExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt);
		void TypeCheckBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt, bool createScope = true);
		void TypeCheckVariableStatement(const std::shared_ptr<AST::VariableStatement>& varStmt);
		void TypeCheckControlStatement(const std::shared_ptr<AST::ControlStatement>& ctrlStmt);
		void TypeCheckIterationStatement(const std::shared_ptr<AST::IterationStatement>& iterStmt);
		void TypeCheckWhileStatement(const std::shared_ptr<AST::WhileStatement>& whileStmt);
		void TypeCheckDoWhileStatement(const std::shared_ptr<AST::DoWhileStatement>& doStmt);
		void TypeCheckForStatement(const std::shared_ptr<AST::ForStatement>& forStmt);
		void TypeCheckFunctionStatement(const std::shared_ptr<AST::FunctionStatement>& functionStmt);
		void TypeCheckReturnStatement(const std::shared_ptr<AST::ReturnStatement>& returnStmt);

		Type TypeCheckExpression(const std::shared_ptr<AST::Expression>& expr);
		Type TypeCheckLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr);
		Type TypeCheckIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr);
		Type TypeCheckAssignmentExpression(const std::shared_ptr<AST::AssignmentExpression>& assignExpr);
		Type TypeCheckAssignmentExpressionAssignment(Type lhsType, Type rightType, const std::shared_ptr<AST::AssignmentExpression>& assignExpr);
		Type TypeCheckAssignmentExpressionAssignmentArithmetic(Type lhsType, Type rightType, const std::shared_ptr<AST::AssignmentExpression>& assignExpr);
		Type TypeCheckAssignmentExpressionAssignmentBitwsie(Type lhsType, Type rightType, const std::shared_ptr<AST::AssignmentExpression>& assignExpr);
		Type TypeCheckBinaryExpression(const std::shared_ptr<AST::BinaryExpression>& binaryExpr);
		Type TypeCheckBinaryExpressionArithmetic(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr);
		Type TypeCheckBinaryExpressionRelational(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr);
		Type TypeCheckBinaryExpressionLogical(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr);
		Type TypeCheckBinaryExpressionBitwise(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr);
		Type TypeCheckCallExpression(const std::shared_ptr<AST::CallExpression>& callExpr);
		Type TypeCheckUnaryExpression(const std::shared_ptr<AST::UnaryExpression>& unaryExpr);
		Type TypeCheckPostfixExpression(const std::shared_ptr<AST::PostfixExpression>& postfixExpr);

	private:
		Type LexerToTypeCheckerType(TokenType type);
		void BeginBlockScope();
		void EndBlockScope();

	private:
		std::shared_ptr<Environment<Type>> m_TypeEnvironment;
		std::shared_ptr<Environment<FunctionType>> m_FunctionEnvironment;
	};
}
