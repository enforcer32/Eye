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
			| VariableStatement
			| IfStatement
			;
	*/
	StatementNode* Parser::Statement()
	{
		switch (m_LookAhead.Type)
		{
		case TokenType::Symbol:
			if (m_LookAhead.Char == '{')
				return BlockStatement();
		case TokenType::Keyword:
			if (!std::strcmp(m_LookAhead.String, "auto"))
				return VariableStatement();
			else if (!std::strcmp(m_LookAhead.String, "if"))
				return IfStatement();
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
		VariableStatement
			: 'auto' VariableDeclarationList ';'
			;
	*/
	VariableStatementNode* Parser::VariableStatement()
	{
		EatToken(TokenType::Keyword, "auto");
		VariableStatementNode* variableStatementNode = new VariableStatementNode(VariableDeclarationList());
		EatToken(TokenType::Symbol, ';');
		return variableStatementNode;
	}

	/*
		VariableDeclarationList
			: VariableDeclaration
			| VariableDeclarationList ',' VariableDeclaration
			;
	*/
	std::vector<VariableDeclarationNode*> Parser::VariableDeclarationList()
	{
		std::vector<VariableDeclarationNode*> variableDeclarationList;
		do
		{
			variableDeclarationList.push_back(VariableDeclaration());
		} while (m_LookAhead.Type == TokenType::Operator && !std::strcmp(m_LookAhead.String, ",") && EatToken(TokenType::Operator, ","));
		return variableDeclarationList;
	}

	/*
		VariableDeclaration
			: Identifier OptionalVariableInitializer
			;

		VariableInitializer
			: '=' AssignmentExpression
			;
	*/
	VariableDeclarationNode* Parser::VariableDeclaration()
	{
		IdentifierNode* identifier = Identifier();

		VariableDeclarationNode* variableDeclarationNode;
		if ((m_LookAhead.Type != TokenType::Symbol || m_LookAhead.Char != ';') && (m_LookAhead.Type != TokenType::Operator || std::strcmp(m_LookAhead.String, ",")))
			return new VariableDeclarationNode(identifier, VariableInitializer());
		return new VariableDeclarationNode(identifier, nullptr);
	}

	/*
		VariableInitializer
			: '=' AssignmentExpression
			;
	*/
	ExpressionNode* Parser::VariableInitializer()
	{
		EatToken(TokenType::Operator, "=");
		return AssignmentExpression();
	}

	/*
		IfStatement
			: 'if' '(' Expression ')' Statement
			| 'if' '(' Expression ')' Statement 'else' Statement
			;
	*/
	IfStatementNode* Parser::IfStatement()
	{
		EatToken(TokenType::Keyword, "if");
		EatToken(TokenType::Operator, "(");
		ExpressionNode* condition = Expression();
		EatToken(TokenType::Symbol, ')');
		StatementNode* consequent = Statement();
		StatementNode* alternate = nullptr;
		if (m_LookAhead.Type == TokenType::Keyword && !std::strcmp(m_LookAhead.String, "else"))
		{
			EatToken(TokenType::Keyword, "else");
			alternate = Statement();
		}
		IfStatementNode* ifStatementNode = new IfStatementNode(condition, consequent, alternate);
		return ifStatementNode;
	}

	/*
		Expression
			: AssignmentExpression
			;
	*/
	ExpressionNode* Parser::Expression()
	{
		return AssignmentExpression();
	}

	/*
		AssignmentExpression
			: RelationalExpression
			| LHSExpression AssignmentOperator AssignmentExpression
			;
	*/
	ExpressionNode* Parser::AssignmentExpression()
	{
		ExpressionNode* left = RelationalExpression();
		
		if (!IsAssignmentOperator(m_LookAhead))
			return left;

		// Validate LHS
		if (left->GetType() != ExpressionNodeType::LHSExpression || ((LHSExpressionNode*)left)->GetLHSType() != LHSExpressionType::Identifier)
			EYE_LOG_CRITICAL("Parser->Bad LHSType: {}, Expected: {}", (int)((LHSExpressionNode*)left)->GetLHSType(), (int)((LHSExpressionNode*)left)->GetLHSType());

		Token op = EatToken(TokenType::Operator, m_LookAhead.String);
		AssignmentExpressionNode* assignmentExpression = new AssignmentExpressionNode((LHSExpressionNode*)left, op, AssignmentExpression());
		return assignmentExpression;
	}

	/*
		RelationalExpression
			: AdditiveBinaryExpression
			| AdditiveBinaryExpression RelationalOperator RelationalExpression
			;
	*/
	ExpressionNode* Parser::RelationalExpression()
	{
		ExpressionNode* left = AdditiveBinaryExpression();

		while (IsRelationalOperator(m_LookAhead))
		{
			Token op = EatToken(TokenType::Operator, m_LookAhead.String);
			ExpressionNode* right = AdditiveBinaryExpression();

			left = new BinaryExpressionNode(left, op, right);
		}

		return left;
	}

	/*
		LHSExpression
			: Identifier
			;

		Identifier
			: IDENTIFIER
			;
	*/
	ExpressionNode* Parser::LHSExpression()
	{
		LHSExpressionNode* lhsExpression = new LHSExpressionNode(Identifier());
		return lhsExpression;
	}

	/*
		Identifier
			: IDENTIFIER
			;
	*/
	IdentifierNode* Parser::Identifier()
	{
		return new IdentifierNode(EatToken(TokenType::Identifier));
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

	//(2+3)*5;
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
			| ParenthesizedExpression
			| LHSExpression
			;
	*/
	ExpressionNode* Parser::PrimaryExpression()
	{
		if (m_LookAhead.Type == TokenType::Number || m_LookAhead.Type == TokenType::String)
			return Literal();

		if (m_LookAhead.Type == TokenType::Operator && !std::strcmp(m_LookAhead.String, "("))
			return ParenthesizedExpression();

		return LHSExpression();
	}

	/*
		ParenthesizedExpression
			: '(' Expression ')'
			;
	*/
	ExpressionNode* Parser::ParenthesizedExpression()
	{
		EatToken(TokenType::Operator, "(");
		ExpressionNode* expression = Expression();
		EatToken(TokenType::Symbol, ')');
		return expression;
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
			EYE_LOG_CRITICAL("Parser->Unexpected Literal Type: {}", (int)m_LookAhead.Type);
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

	/*
		AssignmentOperator
			: '='
			| '+='
			| '-='
			| '**='
			| '/='
			| '%='
			;
	*/
	bool Parser::IsAssignmentOperator(Token token)
	{
		return (token.Type == TokenType::Operator && (!std::strcmp(token.String, "=")
			|| !std::strcmp(token.String, "+=")
			|| !std::strcmp(token.String, "-=")
			|| !std::strcmp(token.String, "*=")
			|| !std::strcmp(token.String, "/=")
			|| !std::strcmp(token.String, "%=")));
	}

	/*
		RelationalOperator
			: '<'
			| '<='
			| '>'
			| '>='
			;
	*/
	bool Parser::IsRelationalOperator(Token token)
	{
		return (token.Type == TokenType::Operator && (!std::strcmp(token.String, "<")
			|| !std::strcmp(token.String, "<=")
			|| !std::strcmp(token.String, ">")
			|| !std::strcmp(token.String, ">=")));
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

		if (token.Type != type || value != token.String)
			EYE_LOG_CRITICAL("Parser->Unexpected Operator Token Type: {}, Expected: {}", (int)token.Type, value);

		m_LookAhead = NextToken();
		return token;
	}

	Token Parser::EatToken(TokenType type, char value)
	{
		Token token = m_LookAhead;

		if (!token)
			EYE_LOG_CRITICAL("Parser->Unexpected LookAhead TokenType: {}, Expected: {}", (int)token.Type, value);

		if (token.Type != type || value != token.Char)
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
