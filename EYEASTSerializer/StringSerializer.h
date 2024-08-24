#pragma once

#include "EYEASTSerializer/ASTSerializer.h"

#include <EYEAST/Statements/ExpressionStatement.h>
#include <EYEAST/Expressions/LiteralExpression.h>

namespace Eye
{
	namespace ASTSerializer
	{
		class StringSerializer : public ASTSerializer
		{
		public:
			virtual std::string Serialize(const std::shared_ptr<AST::Program>& ast) override;

		private:
			std::string SerializeStatement(const std::shared_ptr<AST::Statement>& stmt);
			std::string SerializeExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt);

			std::string SerializeExpression(const std::shared_ptr<AST::Expression>& expr);
			std::string SerializeLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr);
		};
	}
}
