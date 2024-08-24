#include "EYEParser/Parser.h"

#include <EYEUtility/Logger.h>

#define EYEPARSER_THROW_UNEXPECTED_TOKEN(unexpectedToken, expectedToken, line, col, filename) EYE_LOG_CRITICAL("EYEParser->Unexpected Token : {}\n\t on line {}, col {} in file {}\n\tExpected Token: {}", unexpectedToken, line, col, filename, expectedToken)

namespace Eye
{
	namespace Parser
	{
		bool Parser::Parse(const std::vector<Lexer::Token>& tokens)
		{
			m_Tokens = tokens;
			m_CurrentTokenIndex = 0;
			m_LookAhead = NextToken();
			m_Program = Program();
			return true;
		}

		std::shared_ptr<AST::Program> Parser::GetAST() const
		{
			return m_Program;
		}

		/*
			Program
				: StatementList
				;
		*/
		std::shared_ptr<AST::Program> Parser::Program()
		{
			return std::make_shared<AST::Program>(StatementList());
		}

		/*
			StatementList
				: Statement
				| StatementList Statement
				;
		*/
		std::vector<std::shared_ptr<AST::Statement>> Parser::StatementList()
		{
			std::vector<std::shared_ptr<AST::Statement>> statementList;
			while (m_LookAhead && m_LookAhead.GetType() != Lexer::TokenType::EndOfFile)
				statementList.push_back(Statement());
			return statementList;
		}

		/*
			Statement
				: ExpressionStatement
				| BlockStatement
				| VariableStatement
				| ControlStatement
				| IterationStatement
				| FunctionStatement
				| ReturnStatement
				| StructStatement
				;
		*/
		std::shared_ptr<AST::Statement> Parser::Statement()
		{
			switch (m_LookAhead.GetType())
			{
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
		std::shared_ptr<AST::ExpressionStatement> Parser::ExpressionStatement()
		{
			std::shared_ptr<AST::Expression> expression = Expression();
			EatToken(Lexer::TokenType::SymbolSemiColon);
			return std::make_shared<AST::ExpressionStatement>(expression);
		}

		/*
			Expression
				: PrimaryExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::Expression()
		{
			return PrimaryExpression();
		}

		/*
			PrimaryExpression
				: LiteralExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::PrimaryExpression()
		{
			if (IsLookAheadLiteral())
				return LiteralExpression();
			return nullptr;
		}

		/*
			LiteralExpression
				: IntegerLiteral
				| FloatLtieral
				| StringLiteral
				| BooleanLiteral
				| NullLiteral
				;
		*/
		std::shared_ptr<AST::LiteralExpression> Parser::LiteralExpression()
		{
			switch (m_LookAhead.GetType())
			{
			case Lexer::TokenType::LiteralInteger:
				return IntegerLiteral();
			case Lexer::TokenType::LiteralFloat:
				return FloatLiteral();
			case Lexer::TokenType::LiteralString:
				return StringLiteral();
			case Lexer::TokenType::LiteralBoolean:
				return BooleanLiteral();
			case Lexer::TokenType::LiteralNull:
				return NullLiteral();
			default:
				EYEPARSER_THROW_UNEXPECTED_TOKEN(Lexer::TokenTypeStr[(int)m_LookAhead.GetType()], "Literal", m_LookAhead.GetPosition().Line, m_LookAhead.GetPosition().Col, m_LookAhead.GetPosition().FileName);
				break;
			}

			return nullptr;
		}

		/*
			IntegerLiteral
				: INTEGER
				;
		*/
		std::shared_ptr<AST::LiteralExpression> Parser::IntegerLiteral()
		{
			Lexer::Token token = EatToken(Lexer::TokenType::LiteralInteger);
			return std::make_shared<AST::LiteralExpression>((AST::LiteralIntegerType)token.GetValue<Lexer::IntegerType>());
		}

		/*
			FloatLiteral
				: FLOAT
				;
		*/
		std::shared_ptr<AST::LiteralExpression> Parser::FloatLiteral()
		{
			Lexer::Token token = EatToken(Lexer::TokenType::LiteralFloat);
			return std::make_shared<AST::LiteralExpression>((AST::LiteralFloatType)token.GetValue<Lexer::FloatType>());
		}
		
		/*
			StringLiteral
				: STRING
				;
		*/
		std::shared_ptr<AST::LiteralExpression> Parser::StringLiteral()
		{
			Lexer::Token token = EatToken(Lexer::TokenType::LiteralString);
			return std::make_shared<AST::LiteralExpression>((AST::LiteralStringType)token.GetValue<Lexer::StringType>());
		}
		
		/*
			BooleanLiteral
				: BOOL
				;
		*/
		std::shared_ptr<AST::LiteralExpression> Parser::BooleanLiteral()
		{
			Lexer::Token token = EatToken(Lexer::TokenType::LiteralBoolean);
			return std::make_shared<AST::LiteralExpression>((AST::LiteralBooleanType)token.GetValue<Lexer::BooleanType>());
		}
		
		/*
			NullLiteral
				: NULL
				;
		*/
		std::shared_ptr<AST::LiteralExpression> Parser::NullLiteral()
		{
			Lexer::Token token = EatToken(Lexer::TokenType::LiteralNull);
			return std::make_shared<AST::LiteralExpression>(AST::LiteralType::Null);
		}

		bool Parser::IsLookAhead(Lexer::TokenType type)
		{
			return (m_LookAhead.GetType() == type);
		}

		bool Parser::IsLookAheadLiteral()
		{
			return (IsLookAhead(Lexer::TokenType::LiteralInteger) || IsLookAhead(Lexer::TokenType::LiteralFloat) || IsLookAhead(Lexer::TokenType::LiteralString) || IsLookAhead(Lexer::TokenType::LiteralBoolean) || IsLookAhead(Lexer::TokenType::LiteralNull));
		}

		bool Parser::HasToken() const
		{
			return m_CurrentTokenIndex < m_Tokens.size();
		}

		Lexer::Token Parser::NextToken()
		{
			if (!HasToken())
				return {};

			Lexer::Token token = m_Tokens[m_CurrentTokenIndex++];
			while (token && (token.GetType() == Lexer::TokenType::Newline || token.GetType() == Lexer::TokenType::Comment || (token.GetType() == Lexer::TokenType::SymbolBackslash)))
			{
				if (HasToken())
					token = m_Tokens[m_CurrentTokenIndex++];
				else
					return {};
			}

			return token;
		}

		Lexer::Token Parser::PeekToken()
		{
			if (!HasToken())
				return {};

			Lexer::Token token = m_Tokens[m_CurrentTokenIndex];
			while (token && (token.GetType() == Lexer::TokenType::Newline || token.GetType() == Lexer::TokenType::Comment || (token.GetType() == Lexer::TokenType::SymbolBackslash)))
			{
				if (HasToken())
					token = m_Tokens[++m_CurrentTokenIndex];
				else
					return {};
			}

			return token;
		}

		Lexer::Token Parser::EatToken(Lexer::TokenType type)
		{
			Lexer::Token token = m_LookAhead;
			if (!token || token.GetType() != type)
				EYEPARSER_THROW_UNEXPECTED_TOKEN(Lexer::TokenTypeStr[(int)token.GetType()], Lexer::TokenTypeStr[(int)type], token.GetPosition().Line, token.GetPosition().Col, token.GetPosition().FileName);
			m_LookAhead = NextToken();
			return token;
		}
	}
}
