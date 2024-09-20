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
			virtual std::string Serialize(const std::shared_ptr<AST::Program>& ast) override;

		private:
			std::string SerializeStatement(const std::shared_ptr<AST::Statement>& stmt);
			std::string SerializeExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt);
			std::string SerializeBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt);
			std::string SerializeVariableStatement(const std::shared_ptr<AST::VariableStatement>& variableStmt);
			std::string SerializeVariableDeclaration(const std::shared_ptr<AST::VariableDeclaration>& variableDeclaration);
			std::string SerializeControlStatement(const std::shared_ptr<AST::ControlStatement>& controlStmt);
			std::string SerializeIterationStatement(const std::shared_ptr<AST::IterationStatement>& iterationStmt);
			std::string SerializeContinueStatement(const std::shared_ptr<AST::ContinueStatement>& continueStmt);
			std::string SerializeBreakStatement(const std::shared_ptr<AST::BreakStatement>& breakStmt);
			std::string SerializeWhileStatement(const std::shared_ptr<AST::WhileStatement>& whileStmt);
			std::string SerializeDoWhileStatement(const std::shared_ptr<AST::DoWhileStatement>& doWhileStmt);
			std::string SerializeForStatement(const std::shared_ptr<AST::ForStatement>& forStmt);
			std::string SerializeFunctionStatement(const std::shared_ptr<AST::FunctionStatement>& functionStmt);
			std::string SerializeFunctionParameter(const std::shared_ptr<AST::FunctionParameter>& functionParam);
			std::string SerializeReturnStatement(const std::shared_ptr<AST::ReturnStatement>& returnStmt);

			std::string SerializeExpression(const std::shared_ptr<AST::Expression>& expr);
			std::string SerializeLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr);
			std::string SerializeBinaryExpression(const std::shared_ptr<AST::BinaryExpression>& binaryExpr);
			std::string SerializeIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr);
			std::string SerializeAssignmentExpression(const std::shared_ptr<AST::AssignmentExpression>& assignmentExpr);
			std::string SerializeUnaryExpression(const std::shared_ptr<AST::UnaryExpression>& unaryExpr);
			std::string SerializeMemberExpression(const std::shared_ptr<AST::MemberExpression>& memberExpr);
			std::string SerializeCallExpression(const std::shared_ptr<AST::CallExpression>& callExpr);
			std::string SerializePostfixExpression(const std::shared_ptr<AST::PostfixExpression>& postfixExpr);
		};
	}
}
