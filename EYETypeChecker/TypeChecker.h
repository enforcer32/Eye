#pragma once

#include "EYETypeChecker/Type.h"

#include <EYEAST/Program.h>

#include <EYEAST/Statements/Statement.h>
#include <EYEAST/Statements/ExpressionStatement.h>

#include <EYEAST/Expressions/Expression.h>
#include <EYEAST/Expressions/LiteralExpression.h>
#include <EYEAST/Expressions/BinaryExpression.h>

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

			Type TypeCheckExpression(const std::shared_ptr<AST::Expression>& expr);
			Type TypeCheckLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr);
			Type TypeCheckBinaryExpression(const std::shared_ptr<AST::BinaryExpression>& binaryExpr);
		};
	}
}
