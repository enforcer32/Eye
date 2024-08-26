#include "EYEParser/Parser.h"

#include <EYEUtility/Logger.h>

#define EYEPARSER_THROW_UNEXPECTED_TOKEN(unexpectedToken, expectedToken, line, col, filename) EYE_LOG_CRITICAL("EYEParser->Unexpected Token : {}\n\t on line {}, col {} in file {}\n\tExpected Token : {}", unexpectedToken, line, col, filename, expectedToken)
#define EYEPARSER_THROW_UNEXPECTED(unexpecteD, expected, line, col, filename) EYE_LOG_CRITICAL("EYEParser->Unexpected : {}\n\t on line {}, col {} in file {}\n\tExpected : {}", unexpecteD, line, col, filename, expected)

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
				: AdditiveBinaryExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::Expression()
		{
			return AssignmentExpression();
		}

		/*
			AssignmentExpression
				: LogicalORExpression
				| LHSExpression AssignmentOperator AssignmentExpression
		*/
		std::shared_ptr<AST::Expression> Parser::AssignmentExpression()
		{
			std::shared_ptr<AST::Expression> left = LogicalORExpression();

			if (!IsAssignmentOperator(m_LookAhead))
				return left;

			if (!IsLHSExpression(left))
				EYEPARSER_THROW_UNEXPECTED(Lexer::TokenTypeStr[(int)left->GetType()], "Identifier", m_LookAhead.GetPosition().Line, m_LookAhead.GetPosition().Col, m_LookAhead.GetPosition().FileName);

			Lexer::Token op = EatToken(m_LookAhead.GetType());
			return std::make_shared<AST::AssignmentExpression>(op, left, AssignmentExpression());
		}

		/*
			LogicalORExpression
				: LogicalANDExpression '||' LogicalORExpression
				| LogicalORExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::LogicalORExpression()
		{
			std::shared_ptr<AST::Expression> left = LogicalANDExpression();
			while (IsLookAhead(Lexer::TokenType::OperatorLogicalOR))
			{
				Lexer::Token op = EatToken(m_LookAhead.GetType());
				std::shared_ptr<AST::Expression> right = LogicalANDExpression();
				left = std::make_shared<AST::BinaryExpression>(op, left, right);
			}
			return left;
		}

		/*
			LogicalANDExpression
				: EqualityExpression '&&' LogicalANDExpression
				| EqualityExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::LogicalANDExpression()
		{
			std::shared_ptr<AST::Expression> left = EqualityExpression();
			while (IsLookAhead(Lexer::TokenType::OperatorLogicalAND))
			{
				Lexer::Token op = EatToken(m_LookAhead.GetType());
				std::shared_ptr<AST::Expression> right = EqualityExpression();
				left = std::make_shared<AST::BinaryExpression>(op, left, right);
			}
			return left;
		}

		/*
			EqualityExpression
				: RelationalExpression EqualityOperator EqualityExpression
				| RelationalExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::EqualityExpression()
		{
			std::shared_ptr<AST::Expression> left = RelationalExpression();
			while (IsEqualityOperator(m_LookAhead))
			{
				Lexer::Token op = EatToken(m_LookAhead.GetType());
				std::shared_ptr<AST::Expression> right = RelationalExpression();
				left = std::make_shared<AST::BinaryExpression>(op, left, right);
			}
			return left;
		}

		/*
			RelationalExpression
				: AdditiveBinaryExpression
				| AdditiveBinaryExpression RelationalOperator RelationalExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::RelationalExpression()
		{
			std::shared_ptr<AST::Expression> left = AdditiveBinaryExpression();
			while (IsRelationalOperator(m_LookAhead))
			{
				Lexer::Token op = EatToken(m_LookAhead.GetType());
				std::shared_ptr<AST::Expression> right = AdditiveBinaryExpression();
				left = std::make_shared<AST::BinaryExpression>(op, left, right);
			}
			return left;
		}

		/*
			AdditiveBinaryExpression
				: MultiplicativeBinaryExpression
				| AdditiveBinaryExpression AdditiveOperator MultiplicativeBinaryExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::AdditiveBinaryExpression()
		{
			std::shared_ptr<AST::Expression> left = MultiplicativeBinaryExpression();
			while (IsAdditiveOperator(m_LookAhead))
			{
				Lexer::Token op = EatToken(m_LookAhead.GetType());
				std::shared_ptr<AST::Expression> right = MultiplicativeBinaryExpression();
				left = std::make_shared<AST::BinaryExpression>(op, left, right);
			}
			return left;
		}

		/*
			MultiplicativeBinaryExpression
				: UnaryExpression
				| MultiplicativeBinaryExpression MultiplicativeOperator UnaryExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::MultiplicativeBinaryExpression()
		{
			std::shared_ptr<AST::Expression> left = UnaryExpression();
			while (IsMultiplicativeOperator(m_LookAhead))
			{
				Lexer::Token op = EatToken(m_LookAhead.GetType());
				std::shared_ptr<AST::Expression> right = UnaryExpression();
				left = std::make_shared<AST::BinaryExpression>(op, left, right);
			}
			return left;
		}

		/*
			UnaryExpression
				: LHSExpression
				| UnaryOperator UnaryExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::UnaryExpression()
		{
			if (IsUnaryOperator(m_LookAhead))
			{
				Lexer::Token op = EatToken(m_LookAhead.GetType());
				return std::make_shared<AST::UnaryExpression>(op, UnaryExpression());
			}

			return LHSExpression();
		}

		/*
			LHSExpression
				: PrimaryExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::LHSExpression()
		{
			return PrimaryExpression();
		}

		/*
			PrimaryExpression
				: LiteralExpression
				| ParenthesizedExpression
				| IdentifierExpression
				;
		*/
		std::shared_ptr<AST::Expression> Parser::PrimaryExpression()
		{
			if (IsLiteral(m_LookAhead))
				return LiteralExpression();
			else if (IsLookAhead(Lexer::TokenType::OperatorLeftParenthesis))
				return ParenthesizedExpression();
			else if (IsLookAhead(Lexer::TokenType::Identifier))
				return IdentifierExpression();
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

		/*
			ParenthesizedExpression
				: '(' Expression ')'
				;
		*/
		std::shared_ptr<AST::Expression> Parser::ParenthesizedExpression()
		{
			EatToken(Lexer::TokenType::OperatorLeftParenthesis);
			std::shared_ptr<AST::Expression> expression = Expression();
			EatToken(Lexer::TokenType::SymbolRightParenthesis);
			return expression;
		}

		/*
			IdentifierExpression
				: IdentifierToken
				;
		*/
		std::shared_ptr<AST::IdentifierExpression> Parser::IdentifierExpression()
		{
			return std::make_shared<AST::IdentifierExpression>(EatToken(Lexer::TokenType::Identifier));
		}

		bool Parser::IsLookAhead(Lexer::TokenType type) const
		{
			return (m_LookAhead.GetType() == type);
		}

		/*
			LiteralExpression
				: IntegerLiteral
				| FloatLiteral
				| StringLiteral
				| BooleanLiteral
				| NullLiteral
				;
		*/
		bool Parser::IsLiteral(Lexer::Token token) const
		{
			return (token.GetType() == Lexer::TokenType::LiteralInteger || token.GetType() == Lexer::TokenType::LiteralFloat || token.GetType() == Lexer::TokenType::LiteralString || token.GetType() == Lexer::TokenType::LiteralBoolean || token.GetType() == Lexer::TokenType::LiteralNull);
		}

		/*
			AssignmentOperator
				: '='
				| '+='
				| '-='
				| '*='
				| '/='
				| '%='
				| '&='
				| '|='				| '^='
				| '>>='
				| '<<='
				;
		*/
		bool Parser::IsAssignmentOperator(Lexer::Token token) const
		{
			return (token.GetType() == Lexer::TokenType::OperatorAssignment || token.GetType() == Lexer::TokenType::OperatorAssignmentPlus || token.GetType() == Lexer::TokenType::OperatorAssignmentMinus ||
				token.GetType() == Lexer::TokenType::OperatorAssignmentStar || token.GetType() == Lexer::TokenType::OperatorAssignmentSlash || token.GetType() == Lexer::TokenType::OperatorAssignmentModulo ||
				token.GetType() == Lexer::TokenType::OperatorAssignmentBitwiseAND || token.GetType() == Lexer::TokenType::OperatorAssignmentBitwiseOR || token.GetType() == Lexer::TokenType::OperatorAssignmentBitwiseXOR
				|| token.GetType() == Lexer::TokenType::OperatorAssignmentBitwiseLeftShift || token.GetType() == Lexer::TokenType::OperatorAssignmentBitwiseRightShift || token.GetType() == Lexer::TokenType::OperatorAssignmentBitwiseXOR);
		}

		/*
			EqualityOperator
				: '=='
				| '!=
				;
		*/
		bool Parser::IsEqualityOperator(Lexer::Token token) const
		{
			return (token.GetType() == Lexer::TokenType::OperatorRelationalEquals || token.GetType() == Lexer::TokenType::OperatorRelationalNotEquals);
		}

		/*
			RelationalOperator
				: '<'
				| '<='
				| '>'
				| '>='
				;
		*/
		bool Parser::IsRelationalOperator(Lexer::Token token) const
		{
			return (token.GetType() == Lexer::TokenType::OperatorRelationalSmaller || token.GetType() == Lexer::TokenType::OperatorRelationalSmallerEquals || token.GetType() == Lexer::TokenType::OperatorRelationalGreater ||
				token.GetType() == Lexer::TokenType::OperatorRelationalGreaterEquals);
		}

		/*
			AdditiveOperator
				: '+'
				| '-'
				;
		*/
		bool Parser::IsAdditiveOperator(Lexer::Token token) const
		{
			return (token.GetType() == Lexer::TokenType::OperatorBinaryPlus || token.GetType() == Lexer::TokenType::OperatorBinaryMinus);
		}

		/*
			MultiplicativeOperator
				: '*'
				| '/'
				| '%'
				;
		*/
		bool Parser::IsMultiplicativeOperator(Lexer::Token token) const
		{
			return (token.GetType() == Lexer::TokenType::OperatorBinaryStar || token.GetType() == Lexer::TokenType::OperatorBinarySlash || token.GetType() == Lexer::TokenType::OperatorBinaryModulo);
		}

		/*
			UnaryOperator
				: '+'
				| '-'
				| '!'
				;
		*/
		bool Parser::IsUnaryOperator(Lexer::Token token) const
		{
			return (token.GetType() == Lexer::TokenType::OperatorBinaryPlus || token.GetType() == Lexer::TokenType::OperatorBinaryMinus || token.GetType() == Lexer::TokenType::OperatorLogicalNOT);
		}

		/*
			LHSExpression
				: IdentifierExpression
				;
		*/
		bool Parser::IsLHSExpression(const std::shared_ptr<AST::Expression>& expression) const
		{
			return (expression->GetType() == AST::ExpressionType::IdentifierExpression);
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
