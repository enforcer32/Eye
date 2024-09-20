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
		std::expected<bool, Error::Error> Parse(const std::vector<std::shared_ptr<Token>>& tokens);
		std::shared_ptr<AST::Program> GetAST() const;

	private:
		std::shared_ptr<AST::Program> Program();

		// Statements
		std::vector<std::shared_ptr<AST::Statement>> StatementList(TokenType stopAt = TokenType::Invalid);
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

		// Expressions
		std::shared_ptr<AST::Expression> Expression();
		std::shared_ptr<AST::Expression> AssignmentExpression();
		std::shared_ptr<AST::Expression> LogicalORExpression();
		std::shared_ptr<AST::Expression> LogicalANDExpression();
		std::shared_ptr<AST::Expression> BitwiseORExpression();
		std::shared_ptr<AST::Expression> BitwiseXORExpression();
		std::shared_ptr<AST::Expression> BitwiseANDExpression();
		std::shared_ptr<AST::Expression> EqualityExpression();
		std::shared_ptr<AST::Expression> RelationalExpression();
		std::shared_ptr<AST::Expression> BitwiseShiftExpression();
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

	private:
		bool IsLookAhead(TokenType type) const;
		bool IsLiteral(const std::shared_ptr<Token>& token) const;
		bool IsAssignmentOperator(const std::shared_ptr<Token>& token) const;
		bool IsEqualityOperator(const std::shared_ptr<Token>& token) const;
		bool IsRelationalOperator(const std::shared_ptr<Token>& token) const;
		bool IsBitwiseShiftOperator(const std::shared_ptr<Token>& token) const;
		bool IsAdditiveOperator(const std::shared_ptr<Token>& token) const;
		bool IsMultiplicativeOperator(const std::shared_ptr<Token>& token) const;
		bool IsUnaryOperator(const std::shared_ptr<Token>& token) const;
		bool IsPostfixOperator(const std::shared_ptr<Token>& token) const;
		bool IsTypeQualifierKeyword(const std::shared_ptr<Token>& token) const;
		bool IsDataTypeKeyword(const std::shared_ptr<Token>& token) const;
		bool IsLHSExpression(const std::shared_ptr<AST::Expression>& expression) const;

	private:
		bool HasToken() const;
		std::shared_ptr<Token> NextToken();
		std::shared_ptr<Token> PeekToken();
		std::shared_ptr<Token> EatToken(TokenType type);

	private:
		std::shared_ptr<AST::Program> m_Program;
		std::vector<std::shared_ptr<Token>> m_Tokens;
		size_t m_CurrentTokenIndex;
		std::shared_ptr<Token> m_LookAhead;
	};
}
