#include "Eye/Parser/Parser.h"
#include "Eye/Util/Logger.h"

namespace EYE
{
	ParserResult Parser::Parse(EyeInstance* eyeInstance)
	{
		m_EyeInstance = eyeInstance;
		m_CurrentTokenIndex = 0;
		m_LookAhead = NextToken();

		
		while (HasToken())
		{
			Node node = Program();
			m_Nodes.push_back(node);
		}

		return ParserResult::Successful;
	}

	void Parser::DebugPrintNodes()
	{
		for (const auto& node : m_Nodes)
			std::cout << node << std::endl;
	}

	/*
		Program
			: Literal
			;
	*/
	Node Parser::Program()
	{
		return Literal();
	}

	/*
		Literal
			: NumericLiteral
			| StringLiteral
			;
	*/
	Node Parser::Literal()
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
	Node Parser::NumericLiteral()
	{
		Token token = EatToken(TokenType::Number);
		Node node;
		node.Type = NodeType::Number;
		node.Position = token.Position;
		node.Number = token.Number;
		return node;
	}

	/*
		StringLiteral
			: STRING
			;
	*/
	Node Parser::StringLiteral()
	{
		Token token = EatToken(TokenType::String);
		Node node;
		node.Type = NodeType::String;
		node.Position = token.Position;
		node.String = token.String;
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

	bool Parser::HasToken() const
	{
		return m_CurrentTokenIndex < m_EyeInstance->LexerTokens.size();
	}

	bool Parser::IsLastToken() const
	{
		return m_CurrentTokenIndex == m_EyeInstance->LexerTokens.size() - 1;
	}
}
