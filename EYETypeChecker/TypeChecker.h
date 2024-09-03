#pragma once

#include "EYETypeChecker/Type.h"

#include <EYEAST/Program.h>

#include <EYEAST/Statements/Statement.h>
#include <EYEAST/Statements/ExpressionStatement.h>
#include <EYEAST/Statements/BlockStatement.h>
#include <EYEAST/Statements/VariableStatement.h>

#include <EYEAST/Expressions/Expression.h>
#include <EYEAST/Expressions/LiteralExpression.h>
#include <EYEAST/Expressions/BinaryExpression.h>

#include <EYETypeChecker/TypeEnvironment.h>

namespace Eye
{
	namespace TypeChecker
	{
		class TypeChecker
		{
		public:
			bool TypeCheck(const std::shared_ptr<AST::Program>& ast);

		private:
			void TypeCheckStatement(const std::shared_ptr<AST::Statement>& stmt);
			void TypeCheckExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt);
			void TypeCheckBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt);
			void TypeCheckVariableStatement(const std::shared_ptr<AST::VariableStatement>& varStmt);

			Type TypeCheckExpression(const std::shared_ptr<AST::Expression>& expr);
			Type TypeCheckLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr);
			Type TypeCheckBinaryExpression(const std::shared_ptr<AST::BinaryExpression>& binaryExpr);

		private:
			Type LexerToTypeCheckerType(Lexer::TokenType type);
			void BeginBlockScope();
			void EndBlockScope();

		private:
			std::shared_ptr<TypeEnvironment> m_TypeEnvironment;
		};
	}
}
