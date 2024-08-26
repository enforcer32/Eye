#pragma once

#include <EYELexer/Token.h>
#include <EYEAST/Program.h>
#include <EYEAST/Statements/Statement.h>
#include <EYEAST/Statements/ExpressionStatement.h>
#include <EYEAST/Expressions/Expression.h>
#include <EYEAST/Expressions/LiteralExpression.h>
#include <EYEAST/Expressions/BinaryExpression.h>
#include <EYEAST/Expressions/AssignmentExpression.h>
#include <EYEAST/Expressions/UnaryExpression.h>
#include <EYEAST/Expressions/MemberExpression.h>

namespace Eye
{
	namespace Parser
	{
		class Parser
		{
		public:
			bool Parse(const std::vector<Lexer::Token>& tokens);
			std::shared_ptr<AST::Program> GetAST() const;

		private:
			std::shared_ptr<AST::Program> Program();
			
			// Statements
			std::vector<std::shared_ptr<AST::Statement>> StatementList();
			std::shared_ptr<AST::Statement> Statement();
			std::shared_ptr<AST::ExpressionStatement> ExpressionStatement();

			// Expressions
			std::shared_ptr<AST::Expression> Expression();
			std::shared_ptr<AST::Expression> AssignmentExpression();
			std::shared_ptr<AST::Expression> LogicalORExpression();
			std::shared_ptr<AST::Expression> LogicalANDExpression();
			std::shared_ptr<AST::Expression> EqualityExpression();
			std::shared_ptr<AST::Expression> RelationalExpression();
			std::shared_ptr<AST::Expression> AdditiveBinaryExpression();
			std::shared_ptr<AST::Expression> MultiplicativeBinaryExpression();
			std::shared_ptr<AST::Expression> UnaryExpression();
			std::shared_ptr<AST::Expression> LHSExpression();
			std::shared_ptr<AST::Expression> MemberExpression();
			std::shared_ptr<AST::Expression> PrimaryExpression();
			std::shared_ptr<AST::LiteralExpression> LiteralExpression();
			std::shared_ptr<AST::LiteralExpression> IntegerLiteral();
			std::shared_ptr<AST::LiteralExpression> FloatLiteral();
			std::shared_ptr<AST::LiteralExpression> StringLiteral();
			std::shared_ptr<AST::LiteralExpression> BooleanLiteral();
			std::shared_ptr<AST::LiteralExpression> NullLiteral();
			std::shared_ptr<AST::Expression> ParenthesizedExpression();
			std::shared_ptr<AST::IdentifierExpression> IdentifierExpression();

		private:
			bool IsLookAhead(Lexer::TokenType type) const;
			bool IsLiteral(Lexer::Token token) const;
			bool IsAssignmentOperator(Lexer::Token token) const;
			bool IsEqualityOperator(Lexer::Token token) const;
			bool IsRelationalOperator(Lexer::Token token) const;
			bool IsAdditiveOperator(Lexer::Token token) const;
			bool IsMultiplicativeOperator(Lexer::Token token) const;
			bool IsUnaryOperator(Lexer::Token token) const;
			bool IsLHSExpression(const std::shared_ptr<AST::Expression>& expression) const;

		private:
			bool HasToken() const;
			Lexer::Token NextToken();
			Lexer::Token PeekToken();
			Lexer::Token EatToken(Lexer::TokenType type);

		private:
			std::shared_ptr<AST::Program> m_Program;
			std::vector<Lexer::Token> m_Tokens;
			size_t m_CurrentTokenIndex;
			Lexer::Token m_LookAhead;
		};
	}
}
