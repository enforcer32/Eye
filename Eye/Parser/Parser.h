#pragma once

#include "Eye/Lexer/Token.h"
#include "Eye/Error/Error.h"

#include "Eye/AST/Program.h"
#include "Eye/AST/Statements/Statement.h"
#include "Eye/AST/Statements/ExpressionStatement.h"
#include "Eye/AST/Statements/BlockStatement.h"
#include "Eye/AST/Statements/VariableStatement.h"
#include "Eye/AST/Statements/ControlStatement.h"
#include "Eye/AST/Statements/IterationStatement.h"
#include "Eye/AST/Statements/ContinueStatement.h"
#include "Eye/AST/Statements/BreakStatement.h"
#include "Eye/AST/Statements/FunctionStatement.h"
#include "Eye/AST/Statements/ReturnStatement.h"

#include "Eye/AST/Expressions/Expression.h"
#include "Eye/AST/Expressions/LiteralExpression.h"
#include "Eye/AST/Expressions/BinaryExpression.h"
#include "Eye/AST/Expressions/AssignmentExpression.h"
#include "Eye/AST/Expressions/UnaryExpression.h"
#include "Eye/AST/Expressions/MemberExpression.h"
#include "Eye/AST/Expressions/CallExpression.h"
#include "Eye/AST/Expressions/PostfixExpression.h"


#include <expected>

namespace Eye
{
	class Parser
	{
	public:
		std::expected<std::unique_ptr<AST::Program>, Error::Error> Parse(std::vector<std::unique_ptr<Token>>&& tokens);

	private:
		std::unique_ptr<AST::Program> Program();

		// Statements
		std::vector<std::unique_ptr<AST::Statement>> StatementList(TokenType stopAt = TokenType::Invalid);
		std::unique_ptr<AST::Statement> Statement();
		std::unique_ptr<AST::ExpressionStatement> ExpressionStatement();
		std::unique_ptr<AST::BlockStatement> BlockStatement();
		std::unique_ptr<AST::VariableStatement> VariableStatement();
		std::vector<std::unique_ptr<AST::VariableDeclaration>> VariableDeclarationList();
		std::unique_ptr<AST::VariableDeclaration> VariableDeclaration();
		std::unique_ptr<AST::Expression> VariableInitializer();
		std::unique_ptr<AST::ControlStatement> ControlStatement();
		std::unique_ptr<AST::IterationStatement> IterationStatement();
		std::unique_ptr<AST::ContinueStatement> ContinueStatement();
		std::unique_ptr<AST::BreakStatement> BreakStatement();
		std::unique_ptr<AST::WhileStatement> WhileStatement();
		std::unique_ptr<AST::DoWhileStatement> DoWhileStatement();
		std::unique_ptr<AST::ForStatement> ForStatement();
		std::unique_ptr<AST::FunctionStatement> FunctionStatement();
		std::vector<std::unique_ptr<AST::FunctionParameter>> FunctionParameterList();
		std::unique_ptr<AST::FunctionParameter> FunctionParameter();
		std::unique_ptr<AST::ReturnStatement> ReturnStatement();

		// Expressions
		std::unique_ptr<AST::Expression> Expression();
		std::unique_ptr<AST::Expression> AssignmentExpression();
		std::unique_ptr<AST::Expression> LogicalORExpression();
		std::unique_ptr<AST::Expression> LogicalANDExpression();
		std::unique_ptr<AST::Expression> BitwiseORExpression();
		std::unique_ptr<AST::Expression> BitwiseXORExpression();
		std::unique_ptr<AST::Expression> BitwiseANDExpression();
		std::unique_ptr<AST::Expression> EqualityExpression();
		std::unique_ptr<AST::Expression> RelationalExpression();
		std::unique_ptr<AST::Expression> BitwiseShiftExpression();
		std::unique_ptr<AST::Expression> AdditiveBinaryExpression();
		std::unique_ptr<AST::Expression> MultiplicativeBinaryExpression();
		std::unique_ptr<AST::Expression> UnaryExpression();
		std::unique_ptr<AST::Expression> LHSExpression();
		std::unique_ptr<AST::Expression> MemberExpression();
		std::unique_ptr<AST::Expression> CallExpression(std::unique_ptr<AST::Expression> callee);
		std::vector<std::unique_ptr<AST::Expression>> CallArguments();
		std::unique_ptr<AST::Expression> PostfixExpression();
		std::unique_ptr<AST::Expression> PrimaryExpression();
		std::unique_ptr<AST::LiteralExpression> LiteralExpression();
		std::unique_ptr<AST::LiteralExpression> IntegerLiteral();
		std::unique_ptr<AST::LiteralExpression> FloatLiteral();
		std::unique_ptr<AST::LiteralExpression> StringLiteral();
		std::unique_ptr<AST::LiteralExpression> BooleanLiteral();
		std::unique_ptr<AST::LiteralExpression> NullLiteral();
		std::unique_ptr<AST::Expression> ParenthesizedExpression();
		std::unique_ptr<AST::IdentifierExpression> IdentifierExpression();

	private:
		bool IsLookAhead(TokenType type) const;
		bool IsLiteral(const Token* token) const;
		bool IsAssignmentOperator(const Token* token) const;
		bool IsEqualityOperator(const Token* token) const;
		bool IsRelationalOperator(const Token* token) const;
		bool IsBitwiseShiftOperator(const Token* token) const;
		bool IsAdditiveOperator(const Token* token) const;
		bool IsMultiplicativeOperator(const Token* token) const;
		bool IsUnaryOperator(const Token* token) const;
		bool IsPostfixOperator(const Token* token) const;
		bool IsTypeQualifierKeyword(const Token* token) const;
		bool IsDataTypeKeyword(const Token* token) const;
		bool IsLHSExpression(const AST::Expression* expression) const;

	private:
		bool HasToken() const;
		std::unique_ptr<Token> NextToken();
		const Token* PeekToken();
		std::unique_ptr<Token> EatToken(TokenType type);

	private:
		std::unique_ptr<AST::Program> m_Program;
		std::vector<std::unique_ptr<Token>> m_Tokens;
		size_t m_CurrentTokenIndex;
		std::unique_ptr<Token> m_LookAhead;
	};
}
