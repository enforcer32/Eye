#pragma once

#include "EYEASTSerializer/ASTSerializer.h"

#include <EYEAST/Statements/Statement.h>
#include <EYEAST/Statements/ExpressionStatement.h>
#include <EYEAST/Statements/BlockStatement.h>
#include <EYEAST/Statements/VariableStatement.h>
#include <EYEAST/Statements/ControlStatement.h>
#include <EYEAST/Statements/IterationStatement.h>

#include <EYEAST/Expressions/Expression.h>
#include <EYEAST/Expressions/LiteralExpression.h>
#include <EYEAST/Expressions/BinaryExpression.h>
#include <EYEAST/Expressions/IdentifierExpression.h>
#include <EYEAST/Expressions/AssignmentExpression.h>
#include <EYEAST/Expressions/UnaryExpression.h>
#include <EYEAST/Expressions/MemberExpression.h>
#include <EYEAST/Expressions/CallExpression.h>

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
			std::string SerializeBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt);
			std::string SerializeVariableStatement(const std::shared_ptr<AST::VariableStatement>& variableStmt);
			std::string SerializeVariableDeclaration(const std::shared_ptr<AST::VariableDeclaration>& variableDeclaration);
			std::string SerializeControlStatement(const std::shared_ptr<AST::ControlStatement>& controlStmt);
			std::string SerializeIterationStatement(const std::shared_ptr<AST::IterationStatement>& iterationStmt);
			std::string SerializeWhileStatement(const std::shared_ptr<AST::WhileStatement>& whileStmt);
			std::string SerializeDoWhileStatement(const std::shared_ptr<AST::DoWhileStatement>& doWhileStmt);
			std::string SerializeForStatement(const std::shared_ptr<AST::ForStatement>& forStmt);

			std::string SerializeExpression(const std::shared_ptr<AST::Expression>& expr);
			std::string SerializeLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr);
			std::string SerializeBinaryExpression(const std::shared_ptr<AST::BinaryExpression>& binaryExpr);
			std::string SerializeIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr);
			std::string SerializeAssignmentExpression(const std::shared_ptr<AST::AssignmentExpression>& assignmentExpr);
			std::string SerializeUnaryExpression(const std::shared_ptr<AST::UnaryExpression>& unaryExpr);
			std::string SerializeMemberExpression(const std::shared_ptr<AST::MemberExpression>& memberExpr);
			std::string SerializeCallExpression(const std::shared_ptr<AST::CallExpression>& callExpr);
		};
	}
}
