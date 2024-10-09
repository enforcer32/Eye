#pragma once

#include "Eye/ASTSerializer/ASTSerializer.h"

#include "Eye/AST/Statements/Statement.h"
#include "Eye/AST/Statements/ExpressionStatement.h"
#include "Eye/AST/Statements/BlockStatement.h"
#include "Eye/AST/Statements/VariableStatement.h"
#include "Eye/AST/Statements/ControlStatement.h"
#include "Eye/AST/Statements/IterationStatement.h"
#include "Eye/AST/Statements/ContinueStatement.h"
#include "Eye/AST/Statements/BreakStatement.h"
#include "Eye/AST/Statements/FunctionStatement.h"
#include "Eye/AST/Statements/ReturnStatement.h"

#include "Eye/AST/Expressions/Expression.h"
#include "Eye/AST/Expressions/LiteralExpression.h"
#include "Eye/AST/Expressions/BinaryExpression.h"
#include "Eye/AST/Expressions/IdentifierExpression.h"
#include "Eye/AST/Expressions/AssignmentExpression.h"
#include "Eye/AST/Expressions/UnaryExpression.h"
#include "Eye/AST/Expressions/MemberExpression.h"
#include "Eye/AST/Expressions/CallExpression.h"
#include "Eye/AST/Expressions/PostfixExpression.h"

namespace Eye
{
	namespace ASTSerializer
	{
		class StringSerializer : public ASTSerializer
		{
		public:
			virtual std::string Serialize(const AST::Program* ast) override;

		private:
			std::string SerializeStatement(const AST::Statement* stmt);
			std::string SerializeExpressionStatement(const AST::ExpressionStatement* exprStmt);
			std::string SerializeBlockStatement(const AST::BlockStatement* blockStmt);
			std::string SerializeVariableStatement(const AST::VariableStatement* variableStmt);
			std::string SerializeVariableDeclaration(const AST::VariableDeclaration* variableDeclaration);
			std::string SerializeControlStatement(const AST::ControlStatement* controlStmt);
			std::string SerializeIterationStatement(const AST::IterationStatement* iterationStmt);
			std::string SerializeContinueStatement(const AST::ContinueStatement* continueStmt);
			std::string SerializeBreakStatement(const AST::BreakStatement* breakStmt);
			std::string SerializeWhileStatement(const AST::WhileStatement* whileStmt);
			std::string SerializeDoWhileStatement(const AST::DoWhileStatement* doWhileStmt);
			std::string SerializeForStatement(const AST::ForStatement* forStmt);
			std::string SerializeFunctionStatement(const AST::FunctionStatement* functionStmt);
			std::string SerializeFunctionParameter(const AST::FunctionParameter* functionParam);
			std::string SerializeReturnStatement(const AST::ReturnStatement* returnStmt);

			std::string SerializeExpression(const AST::Expression* expr);
			std::string SerializeLiteralExpression(const AST::LiteralExpression* literalExpr);
			std::string SerializeBinaryExpression(const AST::BinaryExpression* binaryExpr);
			std::string SerializeIdentifierExpression(const AST::IdentifierExpression* identifierExpr);
			std::string SerializeAssignmentExpression(const AST::AssignmentExpression* assignmentExpr);
			std::string SerializeUnaryExpression(const AST::UnaryExpression* unaryExpr);
			std::string SerializeMemberExpression(const AST::MemberExpression* memberExpr);
			std::string SerializeCallExpression(const AST::CallExpression* callExpr);
			std::string SerializePostfixExpression(const AST::PostfixExpression* postfixExpr);
		};
	}
}
