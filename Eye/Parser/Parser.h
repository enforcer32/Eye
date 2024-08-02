#pragma once

#include "Eye/Common/Eye.h"
#include "Eye/Parser/Ast/ProgramNode.h"
#include "Eye/Parser/Ast/StatementNode.h"
#include "Eye/Parser/Ast/LiteralNode.h"
#include "Eye/Parser/Ast/BinaryExpressionNode.h"
#include "Eye/Parser/Ast/AssignmentExpressionNode.h"
#include "Eye/Parser/Ast/LHSExpressionNode.h"
#include "Eye/Parser/Ast/VariableDeclarationNode.h"
#include "Eye/Parser/Ast/Identifier.h"

#include <vector>

namespace EYE
{
	enum class ParserResult
	{
		Successful,
		Failed
	};

	class Parser
	{
	public:
		ParserResult Parse(EyeInstance* eyeInstance);

		// Temporary
		void DebugPrintJSON();
		void DebugPrintString();

	private:
		ProgramNode* Program();
		std::vector<StatementNode*> StatementList(Token stopAt = {});
		StatementNode* Statement();
		ExpressionStatementNode* ExpressionStatement();
		BlockStatementNode* BlockStatement();
		VariableStatementNode* VariableStatement();
		IfStatementNode* IfStatement();
		std::vector<VariableDeclarationNode*> VariableDeclarationList();
		VariableDeclarationNode* VariableDeclaration();
		ExpressionNode* VariableInitializer();
		ExpressionNode* Expression();
		ExpressionNode* AssignmentExpression();
		ExpressionNode* LHSExpression();
		IdentifierNode* Identifier();
		ExpressionNode* AdditiveBinaryExpression();
		ExpressionNode* MultiplicativeBinaryExpression();
		ExpressionNode* PrimaryExpression();
		ExpressionNode* ParenthesizedExpression();
		LiteralNode* Literal();
		LiteralNode* NumericLiteral();
		LiteralNode* StringLiteral();
		
	private:
		bool IsValidAssignmentOperator(Token token);

	private:
		Token NextToken();
		Token PeekToken();
		Token EatToken(TokenType type);
		Token EatToken(TokenType type, const std::string& value);
		Token EatToken(TokenType type, char value);

		bool HasToken() const;
		bool IsLastToken() const;

	private:
		EyeInstance* m_EyeInstance;
		ProgramNode* m_Program;
		size_t m_CurrentTokenIndex;
		Token m_LookAhead;
	};
}
