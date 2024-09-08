#pragma once

#include "EYETypeChecker/Type.h"

#include <EYEError/Error.h>
#include <EYETypeChecker/TypeEnvironment.h>

#include <EYEAST/Program.h>
#include <EYEAST/Statements/Statement.h>
#include <EYEAST/Statements/ExpressionStatement.h>
#include <EYEAST/Statements/BlockStatement.h>
#include <EYEAST/Statements/VariableStatement.h>
#include <EYEAST/Statements/ControlStatement.h>
#include <EYEAST/Statements/IterationStatement.h>

#include <EYEAST/Expressions/Expression.h>
#include <EYEAST/Expressions/LiteralExpression.h>
#include <EYEAST/Expressions/IdentifierExpression.h>
#include <EYEAST/Expressions/BinaryExpression.h>

#include <expected>

namespace Eye
{
	namespace TypeChecker
	{
		class TypeChecker
		{
		public:
			std::expected<bool, Error::Error> TypeCheck(const std::shared_ptr<AST::Program>& ast);

		private:
			void TypeCheckStatement(const std::shared_ptr<AST::Statement>& stmt);
			void TypeCheckExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt);
			void TypeCheckBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt);
			void TypeCheckVariableStatement(const std::shared_ptr<AST::VariableStatement>& varStmt);
			void TypeCheckControlStatement(const std::shared_ptr<AST::ControlStatement>& ctrlStmt);
			void TypeCheckIterationStatement(const std::shared_ptr<AST::IterationStatement>& iterStmt);
			void TypeCheckWhileStatement(const std::shared_ptr<AST::WhileStatement>& whileStmt);
			void TypeCheckDoWhileStatement(const std::shared_ptr<AST::DoWhileStatement>& doStmt);
			void TypeCheckForStatement(const std::shared_ptr<AST::ForStatement>& forStmt);

			Type TypeCheckExpression(const std::shared_ptr<AST::Expression>& expr);
			Type TypeCheckLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr);
			Type TypeCheckIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr);
			Type TypeCheckBinaryExpression(const std::shared_ptr<AST::BinaryExpression>& binaryExpr);
			Type TypeCheckBinaryExpressionArithmeticPlus(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr);
			Type TypeCheckBinaryExpressionRelational(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr);

		private:
			Type LexerToTypeCheckerType(Lexer::TokenType type);
			void BeginBlockScope();
			void EndBlockScope();

		private:
			std::shared_ptr<TypeEnvironment> m_TypeEnvironment;
		};
	}
}
