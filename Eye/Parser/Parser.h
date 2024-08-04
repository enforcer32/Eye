#pragma once

#include "Eye/Common/Eye.h"
#include "Eye/Parser/Ast/ProgramNode.h"
#include "Eye/Parser/Ast/StatementNode.h"
#include "Eye/Parser/Ast/LiteralNode.h"
#include "Eye/Parser/Ast/BinaryExpressionNode.h"
#include "Eye/Parser/Ast/UnaryExpressionNode.h"
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
		void DebugPrintJSON() const;
		void DebugPrintString() const;
		std::string ToJSONString() const;

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
		ExpressionNode* EqualityExpression();
		ExpressionNode* RelationalExpression();
		ExpressionNode* LogicalANDExpression();
		ExpressionNode* LogicalORExpression();
		ExpressionNode* LHSExpression();
		IdentifierNode* Identifier();
		ExpressionNode* UnaryExpression();
		ExpressionNode* AdditiveBinaryExpression();
		ExpressionNode* MultiplicativeBinaryExpression();
		ExpressionNode* PrimaryExpression();
		ExpressionNode* ParenthesizedExpression();
		LiteralNode* Literal();
		LiteralNode* NumericLiteral();
		LiteralNode* StringLiteral();
		LiteralNode* BooleanLiteral();
		LiteralNode* NullLiteral();
		
	private:
		bool IsOperator(Token token, const std::string& type) const;
		bool IsAssignmentOperator(Token token) const;
		bool IsRelationalOperator(Token token) const;
		bool IsEqualityOperator(Token token) const;
		bool IsUnaryOperator(Token token) const;

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
