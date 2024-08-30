#pragma once

#include <EYELexer/Token.h>
#include <EYEAST/Program.h>
#include <EYEAST/Statements/Statement.h>
#include <EYEAST/Statements/ExpressionStatement.h>
#include <EYEAST/Statements/BlockStatement.h>
#include <EYEAST/Statements/VariableStatement.h>
#include <EYEAST/Statements/ControlStatement.h>
#include <EYEAST/Statements/IterationStatement.h>
#include <EYEAST/Statements/ContinueStatement.h>
#include <EYEAST/Statements/BreakStatement.h>
#include <EYEAST/Statements/FunctionStatement.h>
#include <EYEAST/Statements/ReturnStatement.h>
#include <EYEAST/Statements/StructStatement.h>

#include <EYEAST/Expressions/Expression.h>
#include <EYEAST/Expressions/LiteralExpression.h>
#include <EYEAST/Expressions/BinaryExpression.h>
#include <EYEAST/Expressions/AssignmentExpression.h>
#include <EYEAST/Expressions/UnaryExpression.h>
#include <EYEAST/Expressions/MemberExpression.h>
#include <EYEAST/Expressions/CallExpression.h>
#include <EYEAST/Expressions/PostfixExpression.h>
#include <EYEAST/Expressions/NewExpression.h>

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
			std::vector<std::shared_ptr<AST::Statement>> StatementList(Lexer::TokenType stopAt = Lexer::TokenType::Invalid);
			std::shared_ptr<AST::Statement> Statement();
			std::shared_ptr<AST::ExpressionStatement> ExpressionStatement();
			std::shared_ptr<AST::BlockStatement> BlockStatement();
			std::shared_ptr<AST::VariableStatement> VariableStatement();
			std::vector<std::shared_ptr<AST::VariableDeclaration>> VariableDeclarationList();
			std::shared_ptr<AST::VariableDeclaration> VariableDeclaration();
			std::shared_ptr<AST::Expression> VariableInitializer();
			std::shared_ptr<AST::ControlStatement> ControlStatement();
			std::shared_ptr<AST::IterationStatement> IterationStatement();
			std::shared_ptr<AST::ContinueStatement> ContinueStatement();
			std::shared_ptr<AST::BreakStatement> BreakStatement();
			std::shared_ptr<AST::WhileStatement> WhileStatement();
			std::shared_ptr<AST::DoWhileStatement> DoWhileStatement();
			std::shared_ptr<AST::ForStatement> ForStatement();
			std::shared_ptr<AST::FunctionStatement> FunctionStatement();
			std::vector<std::shared_ptr<AST::FunctionParameter>> FunctionParameterList();
			std::shared_ptr<AST::FunctionParameter> FunctionParameter();
			std::shared_ptr<AST::ReturnStatement> ReturnStatement();
			std::shared_ptr<AST::StructStatement> StructStatement();

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
			std::shared_ptr<AST::Expression> CallExpression(const std::shared_ptr<AST::Expression>& callee);
			std::vector<std::shared_ptr<AST::Expression>> CallArguments();
			std::shared_ptr<AST::Expression> PostfixExpression();
			std::shared_ptr<AST::Expression> PrimaryExpression();
			std::shared_ptr<AST::LiteralExpression> LiteralExpression();
			std::shared_ptr<AST::LiteralExpression> IntegerLiteral();
			std::shared_ptr<AST::LiteralExpression> FloatLiteral();
			std::shared_ptr<AST::LiteralExpression> StringLiteral();
			std::shared_ptr<AST::LiteralExpression> BooleanLiteral();
			std::shared_ptr<AST::LiteralExpression> NullLiteral();
			std::shared_ptr<AST::Expression> ParenthesizedExpression();
			std::shared_ptr<AST::IdentifierExpression> IdentifierExpression();
			std::shared_ptr<AST::NewExpression> NewExpression();

		private:
			bool IsLookAhead(Lexer::TokenType type) const;
			bool IsLiteral(Lexer::Token token) const;
			bool IsAssignmentOperator(Lexer::Token token) const;
			bool IsEqualityOperator(Lexer::Token token) const;
			bool IsRelationalOperator(Lexer::Token token) const;
			bool IsAdditiveOperator(Lexer::Token token) const;
			bool IsMultiplicativeOperator(Lexer::Token token) const;
			bool IsUnaryOperator(Lexer::Token token) const;
			bool IsPostfixOperator(Lexer::Token token) const;
			bool IsTypeQualifierKeyword(Lexer::Token token) const;
			bool IsDataTypeKeyword(Lexer::Token token) const;
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
