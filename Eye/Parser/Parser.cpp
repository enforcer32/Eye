#include "Eye/Parser/Parser.h"
#include "Eye/Util/Logger.h"

#include <nlohmann/json.hpp>

namespace EYE
{
	ParserResult Parser::Parse(EyeInstance* eyeInstance)
	{
		m_EyeInstance = eyeInstance;
		m_CurrentTokenIndex = 0;
		m_LookAhead = NextToken();

		m_Program = Program();
		return ParserResult::Successful;
	}

	void Parser::DebugPrintJSON()
	{
		nlohmann::json data = nlohmann::json::parse(m_Program->ToJSON());
		std::cout << data.dump(2) << std::endl;
	}

	void Parser::DebugPrintString()
	{
		std::cout << m_Program->ToJSON() << std::endl;
	}

	/*
		Program
			: StatementList
			;
	*/
	ProgramNode* Parser::Program()
	{
		ProgramNode* program = new ProgramNode(StatementList());
		return program;
	}

	/*
		StatementList
			: Statement
			| StatementList Statement
			;
	*/
	std::vector<StatementNode*> Parser::StatementList(Token stopAt)
	{
		std::vector<StatementNode*> statementList;
		while (m_LookAhead && m_LookAhead != stopAt)
			statementList.push_back(Statement());
		return statementList;
	}

	/*
		Statement
			: ExpressionStatement
			| BlockStatement
			;
	*/
	StatementNode* Parser::Statement()
	{
		switch (m_LookAhead.Type)
		{
		case TokenType::Symbol:
			if (m_LookAhead.Char == '{')
				return BlockStatement();
		default:
			break;
		}
		return ExpressionStatement();
	}

	/*
		ExpressionStatement
			: Expression ';'
			;
	*/
	ExpressionStatementNode* Parser::ExpressionStatement()
	{
		ExpressionStatementNode* expressionStatement = new ExpressionStatementNode(Expression());
		EatToken(TokenType::Symbol, ';');
		return expressionStatement;
	}

	/*
		BlockStatement
			: '{' OptionalStatementList '}'
			;
	*/
	BlockStatementNode* Parser::BlockStatement()
	{
		Token stopAtToken;
		stopAtToken.Type = TokenType::Symbol;
		stopAtToken.Char = '}';

		EatToken(TokenType::Symbol, '{');
		std::vector<StatementNode*> statementList;
		if (m_LookAhead.Type != TokenType::Symbol || m_LookAhead.Char != '}')
			statementList = StatementList(stopAtToken);
		EatToken(TokenType::Symbol, '}');

		BlockStatementNode* blockStatement = new BlockStatementNode(statementList);
		return blockStatement;
	}

	/*
		Expression
			: AdditiveBinaryExpression
			;
	*/
	//2+3+4
	ExpressionNode* Parser::Expression()
	{
		return AdditiveBinaryExpression();
	}

	/*
		AdditiveBinaryExpression
			: MultiplicativeBinaryExpression
			| AdditiveBinaryExpression '+' MultiplicativeBinaryExpression
			| AdditiveBinaryExpression '-' MultiplicativeBinaryExpression
			;
	*/
	ExpressionNode* Parser::AdditiveBinaryExpression()
	{
		ExpressionNode* left = MultiplicativeBinaryExpression();

		// AdditiveBinaryExpression
		while (m_LookAhead.Type == TokenType::Operator && (!std::strcmp(m_LookAhead.String, "+") || !std::strcmp(m_LookAhead.String, "-")))
		{
			Token op = EatToken(TokenType::Operator, m_LookAhead.String);
			ExpressionNode* right = MultiplicativeBinaryExpression();

			left = new BinaryExpressionNode(left, op, right);
		}

		return left;
	}

	/*
	MultiplicativeBinaryExpression
		: PrimaryExpression
		| MultiplicativeBinaryExpression '*' PrimaryExpression
		| MultiplicativeBinaryExpression '/' PrimaryExpression
		;
	*/
	ExpressionNode* Parser::MultiplicativeBinaryExpression()
	{
		ExpressionNode* left = PrimaryExpression();

		while (m_LookAhead.Type == TokenType::Operator && (!std::strcmp(m_LookAhead.String, "*") || !std::strcmp(m_LookAhead.String, "/")))
		{
			Token op = EatToken(TokenType::Operator, m_LookAhead.String);
			ExpressionNode* right = PrimaryExpression();

			left = new BinaryExpressionNode(left, op, right);
		}

		return left;
	}

	/*
		PrimaryExpression
			: Literal
			;
	*/
	ExpressionNode* Parser::PrimaryExpression()
	{
		return Literal();
	}

	/*
		Literal
			: NumericLiteral
			| StringLiteral
			;
	*/
	LiteralNode* Parser::Literal()
	{
		switch (m_LookAhead.Type)
		{
		case TokenType::Number:
			return NumericLiteral();
		case TokenType::String:
			return StringLiteral();
		default:
			EYE_LOG_CRITICAL("Unexpected Literal Type: {}", (int)m_LookAhead.Type);
			break;
		}

		return {};
	}

	/*
		NumericLiteral
			: NUMBER
			;
	*/
	LiteralNode* Parser::NumericLiteral()
	{
		Token token = EatToken(TokenType::Number);
		LiteralNode* node = new LiteralNode(LiteralNodeType::Number, (void*)token.Number);
		return node;
	}

	/*
		StringLiteral
			: STRING
			;
	*/
	LiteralNode* Parser::StringLiteral()
	{
		Token token = EatToken(TokenType::String);
		LiteralNode* node = new LiteralNode(LiteralNodeType::String, (void*)token.String);
		return node;
	}

	Token Parser::NextToken()
	{
		if (!HasToken())
			return {};

		Token token = m_EyeInstance->LexerTokens[m_CurrentTokenIndex++];
		while (token && (token.Type == TokenType::Newline || token.Type == TokenType::Comment || (token.Type == TokenType::Symbol && token.Char == '\\')))
		{
			if (HasToken())
				token = m_EyeInstance->LexerTokens[m_CurrentTokenIndex++];
			else
				return {};
		}

		return token;
	}

	Token Parser::PeekToken()
	{
		if (!HasToken())
			return {};

		Token token = m_EyeInstance->LexerTokens[m_CurrentTokenIndex];
		while (token && (token.Type == TokenType::Newline || token.Type == TokenType::Comment || (token.Type == TokenType::Symbol && token.Char == '\\')))
		{
			if (HasToken())
				token = m_EyeInstance->LexerTokens[++m_CurrentTokenIndex];
			else
				return {};
		}

		return token;
	}

	Token Parser::EatToken(TokenType type)
	{
		Token token = m_LookAhead;

		if (!token)
			EYE_LOG_CRITICAL("Parser->Unexpected LookAhead TokenType: {}, Expected: {}", (int)token.Type, (int)type);

		if (token.Type != type)
			EYE_LOG_CRITICAL("Parser->Unexpected Token Type: {}, Expected: {}", (int)token.Type, (int)type);
		
		m_LookAhead = NextToken();
		return token;
	}

	Token Parser::EatToken(TokenType type, const std::string& value)
	{
		Token token = m_LookAhead;

		if (!token)
			EYE_LOG_CRITICAL("Parser->Unexpected LookAhead TokenType: {}, Expected: {}", (int)token.Type, value);

		if (token.Type != type && value != token.String)
			EYE_LOG_CRITICAL("Parser->Unexpected Operator Token Type: {}, Expected: {}", (int)token.Type, value);

		m_LookAhead = NextToken();
		return token;
	}

	Token Parser::EatToken(TokenType type, char value)
	{
		Token token = m_LookAhead;

		if (!token)
			EYE_LOG_CRITICAL("Parser->Unexpected LookAhead TokenType: {}, Expected: {}", (int)token.Type, value);

		if (token.Type != type && value != token.Char)
			EYE_LOG_CRITICAL("Parser->Unexpected Operator Token Type: {}, Expected: {}", (int)token.Type, value);

		m_LookAhead = NextToken();
		return token;
	}

	bool Parser::HasToken() const
	{
		return m_CurrentTokenIndex < m_EyeInstance->LexerTokens.size();
	}

	bool Parser::IsLastToken() const
	{
		return m_CurrentTokenIndex == m_EyeInstance->LexerTokens.size() - 1;
	}
}
