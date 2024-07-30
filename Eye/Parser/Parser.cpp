#include "Eye/Parser/Parser.h"
#include "Eye/Util/Logger.h"

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

	void Parser::DebugPrintNodes()
	{
		std::cout << m_Program << std::endl;
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
	std::vector<StatementNode*> Parser::StatementList()
	{
		std::vector<StatementNode*> statementList;
		while (m_LookAhead)
			statementList.push_back(Statement());
		return statementList;
	}

	/*
		Statement
			: ExpressionStatement
			;
	*/
	StatementNode* Parser::Statement()
	{
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
		Expression
			: Literal
			;
	*/
	ExpressionNode* Parser::Expression()
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
