#pragma once

#include "Eye/Common/Eye.h"
#include "Eye/Parser/Ast/ProgramNode.h"
#include "Eye/Parser/Ast/StatementNode.h"
#include "Eye/Parser/Ast/LiteralNode.h"
#include "Eye/Parser/Ast/BinaryExpressionNode.h"

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
		void DebugPrintNodes();

	private:
		ProgramNode* Program();
		std::vector<StatementNode*> StatementList(Token stopAt = {});
		StatementNode* Statement();
		ExpressionStatementNode* ExpressionStatement();
		BlockStatementNode* BlockStatement();
		ExpressionNode* Expression();
		LiteralNode* Literal();
		BinaryExpressionNode* BinaryExpression(LiteralNode* left);
		LiteralNode* NumericLiteral();
		LiteralNode* StringLiteral();
		
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
