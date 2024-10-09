#include "Eye/Parser/Parser.h"
#include "Eye/Utility/Logger.h"
#include "Eye/Error/Exceptions/SyntaxErrorException.h"

namespace Eye
{
	std::expected<std::unique_ptr<AST::Program>, Error::Error> Parser::Parse(std::vector<std::unique_ptr<Token>>&& tokens)
	{
		m_Tokens = tokens;
		m_CurrentTokenIndex = 0;

		try
		{
			m_LookAhead = NextToken();
			m_Program = Program();
		}
		catch (const Error::Exceptions::EyeException& ex)
		{
			return std::unexpected(ex.GetError());
		}
		catch (...)
		{
			EYE_LOG_CRITICAL("EYEParser->Parse Unknown Exception!");
		}

		return std::move(m_Program);
	}

	/*
		Program
			: StatementList
			;
	*/
	std::unique_ptr<AST::Program> Parser::Program()
	{
		return std::make_unique<AST::Program>(StatementList());
	}

	/*
		StatementList
			: Statement
			| StatementList Statement
			;
	*/
	std::vector<std::unique_ptr<AST::Statement>> Parser::StatementList(TokenType stopAt)
	{
		std::vector<std::unique_ptr<AST::Statement>> statementList;
		while (m_LookAhead && m_LookAhead->GetType() != TokenType::EndOfFile && m_LookAhead->GetType() != stopAt)
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
			| ContinueStatement
			| BreakStatement
			| FunctionStatement
			| ReturnStatement
			;
	*/
	std::unique_ptr<AST::Statement> Parser::Statement()
	{
		switch (m_LookAhead->GetType())
		{
		case TokenType::SymbolLeftBrace:
			return BlockStatement();
		case TokenType::KeywordTypeQualifierConst:
		case TokenType::KeywordDataTypeInt:
		case TokenType::KeywordDataTypeFloat:
		case TokenType::KeywordDataTypeStr:
		case TokenType::KeywordDataTypeBool:
		case TokenType::KeywordDataTypeVoid:
			return VariableStatement();
		case TokenType::KeywordControlIf:
			return ControlStatement();
		case TokenType::KeywordIterationWhile:
		case TokenType::KeywordIterationDo:
		case TokenType::KeywordIterationFor:
			return IterationStatement();
		case TokenType::KeywordIterationContinue:
			return ContinueStatement();
		case TokenType::KeywordIterationBreak:
			return BreakStatement();
		case TokenType::KeywordFunction:
			return FunctionStatement();
		case TokenType::KeywordReturn:
			return ReturnStatement();
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
	std::unique_ptr<AST::ExpressionStatement> Parser::ExpressionStatement()
	{
		if (IsLookAhead(TokenType::SymbolSemiColon))
		{
			EatToken(TokenType::SymbolSemiColon);
			return nullptr;
		}

		std::unique_ptr<AST::Expression> expression = Expression();
		EatToken(TokenType::SymbolSemiColon);
		return std::make_unique<AST::ExpressionStatement>(expression->GetSource(), expression); // MOVE
	}

	/*
		BlockStatement
			: '{' OptionalStatementList '}'
			;
	*/
	std::unique_ptr<AST::BlockStatement> Parser::BlockStatement()
	{
		const auto& blockToken = EatToken(TokenType::SymbolLeftBrace);
		std::vector<std::unique_ptr<AST::Statement>> statementList;
		if (!IsLookAhead(TokenType::SymbolRightBrace))
			statementList = StatementList(TokenType::SymbolRightBrace);
		EatToken(TokenType::SymbolRightBrace);
		return std::make_unique<AST::BlockStatement>(blockToken->GetSource(), statementList);
	}

	/*
		VariableStatement
			: OptionalTypeQualifier DatatypeKeyword VariableDeclarationList ';'
			;

		DatatypeKeyword
			: 'int'
			| 'float'
			| 'str'
			| 'bool'
			;

		TypeQualifier
			: 'const'
			;
	*/
	std::unique_ptr<AST::VariableStatement> Parser::VariableStatement()
	{
		std::unique_ptr<Token> typeQualifier;
		if (IsTypeQualifierKeyword(m_LookAhead.get()))
			typeQualifier = EatToken(m_LookAhead->GetType());

		if (!IsDataTypeKeyword(m_LookAhead.get()))
			throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		std::unique_ptr<Token> dataType = EatToken(m_LookAhead->GetType());
		const auto& varToken = (typeQualifier ? typeQualifier : dataType);
		std::unique_ptr<AST::VariableStatement> variableStatement = std::make_unique<AST::VariableStatement>(varToken->GetSource(), typeQualifier, dataType, VariableDeclarationList());
		EatToken(TokenType::SymbolSemiColon);
		return variableStatement;
	}

	/*
		VariableDeclarationList
			: VariableDeclaration
			| VariableDeclarationList ',' VariableDeclaration
			;
	*/
	std::vector<std::unique_ptr<AST::VariableDeclaration>> Parser::VariableDeclarationList()
	{
		std::vector<std::unique_ptr<AST::VariableDeclaration>> variableDeclarationList;
		do
		{
			variableDeclarationList.push_back(VariableDeclaration());
		} while (IsLookAhead(TokenType::OperatorComma) && EatToken(TokenType::OperatorComma));
		return variableDeclarationList;
	}

	/*
		VariableDeclaration
			: IdentifierExpression OptionalVariableInitializer
			;
	*/
	std::unique_ptr<AST::VariableDeclaration> Parser::VariableDeclaration()
	{
		std::unique_ptr<AST::IdentifierExpression> identifier = IdentifierExpression();
		if (!IsLookAhead(TokenType::SymbolSemiColon) && !IsLookAhead(TokenType::OperatorComma))
			return std::make_unique<AST::VariableDeclaration>(identifier, VariableInitializer());
		return std::make_unique<AST::VariableDeclaration>(identifier, nullptr);
	}

	/*
		VariableInitializer
			: '=' AssignmentExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::VariableInitializer()
	{
		EatToken(TokenType::OperatorAssignment);
		return AssignmentExpression();
	}

	/*
		ControlStatement
			: 'if' '(' Expression ')' Statement
			| 'if' '(' Expression ')' Statement 'else' Statement
			;
	*/
	std::unique_ptr<AST::ControlStatement> Parser::ControlStatement()
	{
		const auto& ifToken = EatToken(TokenType::KeywordControlIf);
		EatToken(TokenType::OperatorLeftParenthesis);
		std::unique_ptr<AST::Expression> condition = Expression();
		if (!condition)
			throw Error::Exceptions::SyntaxErrorException("Expected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
		EatToken(TokenType::SymbolRightParenthesis);
		std::unique_ptr<AST::Statement> consequent = Statement();
		std::unique_ptr<AST::Statement> alternate = nullptr;
		if (IsLookAhead(TokenType::KeywordControlElse))
		{
			EatToken(TokenType::KeywordControlElse);
			alternate = Statement();
		}
		return std::make_unique<AST::ControlStatement>(ifToken->GetSource(), condition, consequent, alternate);
	}

	/*
		IterationStatement
			: WhileStatement
			| DoWhileStatement
			| ForStatement
			;
	*/
	std::unique_ptr<AST::IterationStatement> Parser::IterationStatement()
	{
		if (IsLookAhead(TokenType::KeywordIterationWhile))
			return WhileStatement();
		else if (IsLookAhead(TokenType::KeywordIterationDo))
			return DoWhileStatement();
		else if (IsLookAhead(TokenType::KeywordIterationFor))
			return ForStatement();

		return nullptr;
	}

	/*
		ContinueStatement
			: 'continue' ';'
			;
	*/
	std::unique_ptr<AST::ContinueStatement> Parser::ContinueStatement()
	{
		const auto& continueToken = EatToken(TokenType::KeywordIterationContinue);
		EatToken(TokenType::SymbolSemiColon);
		return std::make_unique<AST::ContinueStatement>(continueToken->GetSource());
	}

	/*
		BreakStatement
			: 'break' ';'
			;
	*/
	std::unique_ptr<AST::BreakStatement> Parser::BreakStatement()
	{
		const auto& breakToken = EatToken(TokenType::KeywordIterationBreak);
		EatToken(TokenType::SymbolSemiColon);
		return std::make_unique<AST::BreakStatement>(breakToken->GetSource());
	}

	/*
		WhileStatement
			: 'while' '(' Expression ')' Statement
			;
	*/
	std::unique_ptr<AST::WhileStatement> Parser::WhileStatement()
	{
		const auto& whileToken = EatToken(TokenType::KeywordIterationWhile);
		EatToken(TokenType::OperatorLeftParenthesis);
		std::unique_ptr<AST::Expression> condition = Expression();
		if (!condition)
			throw Error::Exceptions::SyntaxErrorException("Expected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
		EatToken(TokenType::SymbolRightParenthesis);
		std::unique_ptr<AST::Statement> body = Statement();
		return std::make_unique<AST::WhileStatement>(whileToken->GetSource(), condition, body);
	}

	/*
		DoWhileStatement
			: 'do' Statement 'while' '(' Expression ')' ';'
			;
	*/
	std::unique_ptr<AST::DoWhileStatement> Parser::DoWhileStatement()
	{
		const auto& doToken = EatToken(TokenType::KeywordIterationDo);
		std::unique_ptr<AST::Statement> body = Statement();
		EatToken(TokenType::KeywordIterationWhile);
		EatToken(TokenType::OperatorLeftParenthesis);
		std::unique_ptr<AST::Expression> condition = Expression();
		if (!condition)
			throw Error::Exceptions::SyntaxErrorException("Expected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
		EatToken(TokenType::SymbolRightParenthesis);
		EatToken(TokenType::SymbolSemiColon);
		return std::make_unique<AST::DoWhileStatement>(doToken->GetSource(), condition, body);
	}

	/*
		ForStatement
			: 'for' '(' OptionalForVariableInitializer ';' OptionalExpression ';' OptionalExpression ')' Statement
			;

		ForVariableInitializer
			: VariableStatement
			| Expression
			;
	*/
	std::unique_ptr<AST::ForStatement> Parser::ForStatement()
	{
		const auto& forToken = EatToken(TokenType::KeywordIterationFor);
		EatToken(TokenType::OperatorLeftParenthesis);

		std::unique_ptr<void> initializer = nullptr;
		AST::ForInitializerType initializerType = AST::ForInitializerType::Null;
		if (!IsLookAhead(TokenType::SymbolSemiColon))
		{
			if (IsTypeQualifierKeyword(m_LookAhead.get()) || IsDataTypeKeyword(m_LookAhead.get()))
			{
				std::unique_ptr<Token> typeQualifier;
				if (IsTypeQualifierKeyword(m_LookAhead.get()))
					typeQualifier = EatToken(m_LookAhead->GetType());

				if (!IsDataTypeKeyword(m_LookAhead.get()))
					throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

				std::unique_ptr<Token> dataType = EatToken(m_LookAhead->GetType());
				const auto& varToken = (typeQualifier ? typeQualifier : dataType);
				initializer = std::make_unique<AST::VariableStatement>(varToken->GetSource(), typeQualifier, dataType, VariableDeclarationList());
				initializerType = AST::ForInitializerType::VariableStatement;
			}
			else
			{
				initializer = Expression();
				initializerType = AST::ForInitializerType::Expression;
			}
		}
		EatToken(TokenType::SymbolSemiColon);

		std::unique_ptr<AST::Expression> condition = (IsLookAhead(TokenType::SymbolSemiColon) ? nullptr : Expression());
		EatToken(TokenType::SymbolSemiColon);

		std::unique_ptr<AST::Expression> update = (IsLookAhead(TokenType::SymbolRightParenthesis) ? nullptr : Expression());
		EatToken(TokenType::SymbolRightParenthesis);

		std::unique_ptr<AST::Statement> body = Statement();
		return std::make_unique<AST::ForStatement>(forToken->GetSource(), initializer, initializerType, condition, update, body);
	}

	/*
		FunctionStatement
			: 'function' DataTypeKeyword Identifier '(' OptionalFunctionParameterList ')' BlockStatement
			;
	*/
	std::unique_ptr<AST::FunctionStatement> Parser::FunctionStatement()
	{
		const auto& functionToken = EatToken(TokenType::KeywordFunction);

		if (!IsDataTypeKeyword(m_LookAhead.get()))
			throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		std::unique_ptr<Token> returnType = EatToken(m_LookAhead->GetType());
		std::unique_ptr<AST::IdentifierExpression> identifier = IdentifierExpression();

		EatToken(TokenType::OperatorLeftParenthesis);
		std::vector<std::unique_ptr<AST::FunctionParameter>> parameters;
		if (!IsLookAhead(TokenType::SymbolRightParenthesis))
			parameters = FunctionParameterList();
		EatToken(TokenType::SymbolRightParenthesis);

		std::unique_ptr<AST::BlockStatement> body = BlockStatement();
		return std::make_unique<AST::FunctionStatement>(functionToken->GetSource(), returnType, identifier, parameters, body);
	}

	/*
		FunctionParameterList
			: FunctionParameter
			| FunctionParameterList ',' FunctionParameter
			;
	*/
	std::vector<std::unique_ptr<AST::FunctionParameter>> Parser::FunctionParameterList()
	{
		std::vector<std::unique_ptr<AST::FunctionParameter>> parameters;
		do
		{
			parameters.push_back(FunctionParameter());
		} while (IsLookAhead(TokenType::OperatorComma) && EatToken(TokenType::OperatorComma));
		return parameters;
	}

	/*
		FunctionParameter
			: OptionalTypeQualifierKeyword DataTypeKeyword IdentifierExpression OptionalVariableInitializer
			;
	*/
	std::unique_ptr<AST::FunctionParameter> Parser::FunctionParameter()
	{
		std::unique_ptr<Token> typeQualifier;
		if (IsTypeQualifierKeyword(m_LookAhead.get()))
			typeQualifier = EatToken(m_LookAhead->GetType());

		if (!IsDataTypeKeyword(m_LookAhead.get()))
			throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		std::unique_ptr<Token> dataType = EatToken(m_LookAhead->GetType());
		std::unique_ptr<AST::IdentifierExpression> identifier = IdentifierExpression();
		if (!IsLookAhead(TokenType::SymbolRightParenthesis) && !IsLookAhead(TokenType::OperatorComma))
			return std::make_unique<AST::FunctionParameter>(typeQualifier, dataType, identifier, VariableInitializer());
		return std::make_unique<AST::FunctionParameter>(typeQualifier, dataType, identifier, nullptr);
	}

	/*
		ReturnStatement
			: 'return' OptionalExpression ';'
			;
	*/
	std::unique_ptr<AST::ReturnStatement> Parser::ReturnStatement()
	{
		const auto& returnToken = EatToken(TokenType::KeywordReturn);
		std::unique_ptr<AST::Expression> expression = (!IsLookAhead(TokenType::SymbolSemiColon)) ? Expression() : nullptr;
		EatToken(TokenType::SymbolSemiColon);
		return std::make_unique<AST::ReturnStatement>(returnToken->GetSource(), expression);
	}

	/*
		Expression
			: AdditiveBinaryExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::Expression()
	{
		return AssignmentExpression();
	}

	/*
		AssignmentExpression
			: LogicalORExpression
			| LHSExpression AssignmentOperator AssignmentExpression
	*/
	std::unique_ptr<AST::Expression> Parser::AssignmentExpression()
	{
		std::unique_ptr<AST::Expression> left = LogicalORExpression();
		if (!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		if (!IsAssignmentOperator(m_LookAhead.get()))
			return left;

		if (!IsLHSExpression(left.get()))
			throw Error::Exceptions::SyntaxErrorException("Unexpected LHSExpression '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
		return std::make_unique<AST::AssignmentExpression>(op->GetSource(), op, left, AssignmentExpression());
	}

	/*
		LogicalORExpression
			: LogicalANDExpression '||' LogicalORExpression
			| LogicalANDExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::LogicalORExpression()
	{
		std::unique_ptr<AST::Expression> left = LogicalANDExpression();
		if(!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		while (IsLookAhead(TokenType::OperatorLogicalOR))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> right = LogicalANDExpression();
			if (!right)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			left = std::make_unique<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		LogicalANDExpression
			: BitwiseORExpression '&&' LogicalANDExpression
			| BitwiseORExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::LogicalANDExpression()
	{
		std::unique_ptr<AST::Expression> left = BitwiseORExpression();
		if (!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		while (IsLookAhead(TokenType::OperatorLogicalAND))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> right = BitwiseORExpression();
			if (!right)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			left = std::make_unique<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		BitwiseORExpression
			: BitwiseXORExpression '|' BitwiseORExpression
			| BitwiseXORExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::BitwiseORExpression()
	{
		std::unique_ptr<AST::Expression> left = BitwiseXORExpression();
		if (!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		while (IsLookAhead(TokenType::OperatorBitwiseBinaryOR))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> right = BitwiseXORExpression();
			if (!right)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			left = std::make_unique<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		BitwiseXORExpression
			: BitwiseANDExpression '^' BitwiseXORExpression
			| BitwiseANDExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::BitwiseXORExpression()
	{
		std::unique_ptr<AST::Expression> left = BitwiseANDExpression();
		if (!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		while (IsLookAhead(TokenType::OperatorBitwiseBinaryXOR))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> right = BitwiseANDExpression();
			if (!right)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			left = std::make_unique<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		BitwiseANDExpression
			: EqualityExpression '&' BitwiseANDExpression
			| EqualityExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::BitwiseANDExpression()
	{
		std::unique_ptr<AST::Expression> left = EqualityExpression();
		if (!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		while (IsLookAhead(TokenType::OperatorBitwiseBinaryAND))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> right = EqualityExpression();
			if (!right)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			left = std::make_unique<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		EqualityExpression
			: RelationalExpression EqualityOperator EqualityExpression
			| RelationalExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::EqualityExpression()
	{
		std::unique_ptr<AST::Expression> left = RelationalExpression();
		if (!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		while (IsEqualityOperator(m_LookAhead.get()))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> right = RelationalExpression();
			if (!right)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			left = std::make_unique<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		RelationalExpression
			: BitwiseShiftExpression
			| BitwiseShiftExpression RelationalOperator RelationalExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::RelationalExpression()
	{
		std::unique_ptr<AST::Expression> left = BitwiseShiftExpression();
		if (!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		while (IsRelationalOperator(m_LookAhead.get()))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> right = BitwiseShiftExpression();
			if (!right)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			left = std::make_unique<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		BitwiseShiftExpression
			: AdditiveBinaryExpression
			| AdditiveBinaryExpression BitwiseShiftOperator BitwiseShiftExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::BitwiseShiftExpression()
	{
		std::unique_ptr<AST::Expression> left = AdditiveBinaryExpression();
		if (!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		while (IsBitwiseShiftOperator(m_LookAhead.get()))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> right = AdditiveBinaryExpression();
			if (!right)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			left = std::make_unique<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		AdditiveBinaryExpression
			: MultiplicativeBinaryExpression
			| AdditiveBinaryExpression AdditiveOperator MultiplicativeBinaryExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::AdditiveBinaryExpression()
	{
		std::unique_ptr<AST::Expression> left = MultiplicativeBinaryExpression();
		if (!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		while (IsAdditiveOperator(m_LookAhead.get()))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> right = MultiplicativeBinaryExpression();
			if (!right)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			left = std::make_unique<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		MultiplicativeBinaryExpression
			: UnaryExpression
			| MultiplicativeBinaryExpression MultiplicativeOperator UnaryExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::MultiplicativeBinaryExpression()
	{
		std::unique_ptr<AST::Expression> left = UnaryExpression();
		if (!left)
			throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		while (IsMultiplicativeOperator(m_LookAhead.get()))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> right = UnaryExpression();
			if (!right)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			left = std::make_unique<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		UnaryExpression
			: LHSExpression
			| UnaryOperator UnaryExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::UnaryExpression()
	{
		if (IsUnaryOperator(m_LookAhead.get()))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::unique_ptr<AST::Expression> unaryExpr = UnaryExpression();
			if (!unaryExpr)
				throw Error::Exceptions::SyntaxErrorException("Unexpected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			return std::make_unique<AST::UnaryExpression>(op->GetSource(), op, unaryExpr);
		}

		return LHSExpression();
	}

	/*
		LHSExpression
			: MemberExpression
			| CallExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::LHSExpression()
	{
		std::unique_ptr<AST::Expression> memberExpression = MemberExpression();
		if (IsLookAhead(TokenType::OperatorLeftParenthesis))
			return CallExpression(std::move(memberExpression));
		return memberExpression;
	}

	/*
		MemberExpression
			: PostfixExpression
			| MemberExpression '.' Identifier
			| MemberExpression '[' Expression ']'
	*/
	std::unique_ptr<AST::Expression> Parser::MemberExpression()
	{
		std::unique_ptr<AST::Expression> obj = PostfixExpression();
		while (IsLookAhead(TokenType::OperatorDot) || IsLookAhead(TokenType::OperatorLeftBracket))
		{
			if (IsLookAhead(TokenType::OperatorDot))
			{
				const auto& op = EatToken(TokenType::OperatorDot);
				std::unique_ptr<AST::IdentifierExpression> prop = IdentifierExpression();
				obj = std::make_unique<AST::MemberExpression>(op->GetSource(), obj, prop, false);
			}
			else if (IsLookAhead(TokenType::OperatorLeftBracket))
			{
				const auto& op = EatToken(TokenType::OperatorLeftBracket);
				std::unique_ptr<AST::Expression> prop = Expression();
				EatToken(TokenType::SymbolRightBracket);
				obj = std::make_unique<AST::MemberExpression>(op->GetSource(), obj, prop, true);
			}
		}
		return obj;
	}

	/*
		CallExpression
			: Callee CallArguments
			;

		Callee
			: MemberExpression
			| CallExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::CallExpression(std::unique_ptr<AST::Expression> callee)
	{
		std::unique_ptr<AST::Expression> callExpression = std::make_unique<AST::CallExpression>(m_LookAhead->GetSource(), callee, CallArguments());
		if (IsLookAhead(TokenType::OperatorLeftParenthesis))
			callExpression = CallExpression(std::move(callExpression));
		return callExpression;
	}

	/*
		CallArguments
			: '(' OptionalCallArgumentList ')'
			;

		CallArgumentList
			: AssignmentExpression
			| CallArgumentList ',' AssignmentExpression
			;
	*/
	std::vector<std::unique_ptr<AST::Expression>> Parser::CallArguments()
	{
		EatToken(TokenType::OperatorLeftParenthesis);
		std::vector<std::unique_ptr<AST::Expression>> arguments;
		if (!IsLookAhead(TokenType::SymbolRightParenthesis))
		{
			do
			{
				arguments.push_back(AssignmentExpression());
			} while (IsLookAhead(TokenType::OperatorComma) && EatToken(TokenType::OperatorComma));
		}
		EatToken(TokenType::SymbolRightParenthesis);
		return arguments;
	}

	/*
		PostfixExpression
			: PrimaryExpression
			| PostfixExpression PostfixOperator
			;
	*/
	std::unique_ptr<AST::Expression> Parser::PostfixExpression()
	{
		std::unique_ptr<AST::Expression> primaryExpression = PrimaryExpression();
		if (IsPostfixOperator(m_LookAhead.get()))
		{
			std::unique_ptr<Token> op = EatToken(m_LookAhead->GetType());
			return std::make_unique<AST::PostfixExpression>(op->GetSource(), op, primaryExpression);
		}
		return primaryExpression;
	}

	/*
		PrimaryExpression
			: LiteralExpression
			| ParenthesizedExpression
			| IdentifierExpression
			;
	*/
	std::unique_ptr<AST::Expression> Parser::PrimaryExpression()
	{
		if (IsLiteral(m_LookAhead.get()))
			return LiteralExpression();
		else if (IsLookAhead(TokenType::OperatorLeftParenthesis))
			return ParenthesizedExpression();
		else if (IsLookAhead(TokenType::Identifier))
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
	std::unique_ptr<AST::LiteralExpression> Parser::LiteralExpression()
	{
		switch (m_LookAhead->GetType())
		{
		case TokenType::LiteralInteger:
			return IntegerLiteral();
		case TokenType::LiteralFloat:
			return FloatLiteral();
		case TokenType::LiteralString:
			return StringLiteral();
		case TokenType::LiteralBoolean:
			return BooleanLiteral();
		case TokenType::LiteralNull:
			return NullLiteral();
		default:
			throw Error::Exceptions::SyntaxErrorException("Unexpected LiteralExpression '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
			break;
		}

		return nullptr;
	}

	/*
		IntegerLiteral
			: INTEGER
			;
	*/
	std::unique_ptr<AST::LiteralExpression> Parser::IntegerLiteral()
	{
		std::unique_ptr<Token> token = EatToken(TokenType::LiteralInteger);
		return std::make_unique<AST::LiteralExpression>(token->GetSource(), (AST::LiteralIntegerType)token->GetValue<IntegerType>());
	}

	/*
		FloatLiteral
			: FLOAT
			;
	*/
	std::unique_ptr<AST::LiteralExpression> Parser::FloatLiteral()
	{
		std::unique_ptr<Token> token = EatToken(TokenType::LiteralFloat);
		return std::make_unique<AST::LiteralExpression>(token->GetSource(), (AST::LiteralFloatType)token->GetValue<FloatType>());
	}

	/*
		StringLiteral
			: STRING
			;
	*/
	std::unique_ptr<AST::LiteralExpression> Parser::StringLiteral()
	{
		std::unique_ptr<Token> token = EatToken(TokenType::LiteralString);
		return std::make_unique<AST::LiteralExpression>(token->GetSource(), (AST::LiteralStringType)token->GetValue<StringType>());
	}

	/*
		BooleanLiteral
			: BOOL
			;
	*/
	std::unique_ptr<AST::LiteralExpression> Parser::BooleanLiteral()
	{
		std::unique_ptr<Token> token = EatToken(TokenType::LiteralBoolean);
		return std::make_unique<AST::LiteralExpression>(token->GetSource(), (AST::LiteralBooleanType)token->GetValue<BooleanType>());
	}

	/*
		NullLiteral
			: NULL
			;
	*/
	std::unique_ptr<AST::LiteralExpression> Parser::NullLiteral()
	{
		std::unique_ptr<Token> token = EatToken(TokenType::LiteralNull);
		return std::make_unique<AST::LiteralExpression>(token->GetSource(), AST::LiteralType::Null);
	}

	/*
		ParenthesizedExpression
			: '(' Expression ')'
			;
	*/
	std::unique_ptr<AST::Expression> Parser::ParenthesizedExpression()
	{
		EatToken(TokenType::OperatorLeftParenthesis);
		std::unique_ptr<AST::Expression> expression = Expression();
		EatToken(TokenType::SymbolRightParenthesis);
		return expression;
	}

	/*
		IdentifierExpression
			: IdentifierToken
			;
	*/
	std::unique_ptr<AST::IdentifierExpression> Parser::IdentifierExpression()
	{
		const auto& id = EatToken(TokenType::Identifier);
		return std::make_unique<AST::IdentifierExpression>(id->GetSource(), id);
	}

	bool Parser::IsLookAhead(TokenType type) const
	{
		return (m_LookAhead->GetType() == type);
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
	bool Parser::IsLiteral(const Token* token) const
	{
		return (token->GetType() == TokenType::LiteralInteger || token->GetType() == TokenType::LiteralFloat || token->GetType() == TokenType::LiteralString || token->GetType() == TokenType::LiteralBoolean || token->GetType() == TokenType::LiteralNull);
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
			| '|='
			| '^='
			| '>>='
			| '<<='
			;
	*/
	bool Parser::IsAssignmentOperator(const Token* token) const
	{
		return (token->GetType() == TokenType::OperatorAssignment || token->GetType() == TokenType::OperatorAssignmentPlus || token->GetType() == TokenType::OperatorAssignmentMinus ||
			token->GetType() == TokenType::OperatorAssignmentStar || token->GetType() == TokenType::OperatorAssignmentSlash || token->GetType() == TokenType::OperatorAssignmentModulo ||
			token->GetType() == TokenType::OperatorAssignmentBitwiseAND || token->GetType() == TokenType::OperatorAssignmentBitwiseOR || token->GetType() == TokenType::OperatorAssignmentBitwiseXOR
			|| token->GetType() == TokenType::OperatorAssignmentBitwiseLeftShift || token->GetType() == TokenType::OperatorAssignmentBitwiseRightShift || token->GetType() == TokenType::OperatorAssignmentBitwiseXOR);
	}

	/*
		EqualityOperator
			: '=='
			| '!=
			;
	*/
	bool Parser::IsEqualityOperator(const Token* token) const
	{
		return (token->GetType() == TokenType::OperatorRelationalEquals || token->GetType() == TokenType::OperatorRelationalNotEquals);
	}

	/*
		RelationalOperator
			: '<'
			| '<='
			| '>'
			| '>='
			;
	*/
	bool Parser::IsRelationalOperator(const Token* token) const
	{
		return (token->GetType() == TokenType::OperatorRelationalSmaller || token->GetType() == TokenType::OperatorRelationalSmallerEquals || token->GetType() == TokenType::OperatorRelationalGreater ||
			token->GetType() == TokenType::OperatorRelationalGreaterEquals);
	}

	/*
		BitwiseShiftOperator
			: '<<'
			| '>>'
			;
	*/
	bool Parser::IsBitwiseShiftOperator(const Token* token) const
	{
		return (token->GetType() == TokenType::OperatorBitwiseLeftShift || token->GetType() == TokenType::OperatorBitwiseRightShift);
	}

	/*
		AdditiveOperator
			: '+'
			| '-'
			;
	*/
	bool Parser::IsAdditiveOperator(const Token* token) const
	{
		return (token->GetType() == TokenType::OperatorBinaryPlus || token->GetType() == TokenType::OperatorBinaryMinus);
	}

	/*
		MultiplicativeOperator
			: '*'
			| '/'
			| '%'
			;
	*/
	bool Parser::IsMultiplicativeOperator(const Token* token) const
	{
		return (token->GetType() == TokenType::OperatorBinaryStar || token->GetType() == TokenType::OperatorBinarySlash || token->GetType() == TokenType::OperatorBinaryModulo);
	}

	/*
		UnaryOperator
			: '+'
			| '-'
			| '!'
			| '++'
			| '--'
			| '~'
			;
	*/
	bool Parser::IsUnaryOperator(const Token* token) const
	{
		return (token->GetType() == TokenType::OperatorBinaryPlus || token->GetType() == TokenType::OperatorBinaryMinus || token->GetType() == TokenType::OperatorLogicalNOT || token->GetType() == TokenType::OperatorArithmeticIncrement || token->GetType() == TokenType::OperatorArithmeticDecrement || token->GetType() == TokenType::OperatorBitwiseNOT);
	}

	/*
		PostfixOperator
			: '++'
			| '--'
			;
	*/
	bool Parser::IsPostfixOperator(const Token* token) const
	{
		return (token->GetType() == TokenType::OperatorArithmeticIncrement || token->GetType() == TokenType::OperatorArithmeticDecrement);
	}

	/*
		TypeQualifier
			: 'const'
			;
	*/
	bool Parser::IsTypeQualifierKeyword(const Token* token) const
	{
		return (token->GetType() == TokenType::KeywordTypeQualifierConst);
	}

	/*
		DatatypeKeyword
			: 'int'
			| 'float'
			| 'str'
			| 'bool'
			;
	*/
	bool Parser::IsDataTypeKeyword(const Token* token) const
	{
		return (token->GetType() == TokenType::KeywordDataTypeInt || token->GetType() == TokenType::KeywordDataTypeFloat || token->GetType() == TokenType::KeywordDataTypeStr || token->GetType() == TokenType::KeywordDataTypeBool || token->GetType() == TokenType::KeywordDataTypeVoid);
	}

	/*
		LHSExpression
			: IdentifierExpression
			;
	*/
	bool Parser::IsLHSExpression(const AST::Expression* expression) const
	{
		return (expression->GetType() == AST::ExpressionType::IdentifierExpression || expression->GetType() == AST::ExpressionType::MemberExpression);
	}

	bool Parser::HasToken() const
	{
		return m_CurrentTokenIndex < m_Tokens.size();
	}

	std::unique_ptr<Token> Parser::NextToken()
	{
		if (!HasToken())
			return {};

		std::unique_ptr<Token> token = std::move(m_Tokens[m_CurrentTokenIndex++]);
		while (token && (token->GetType() == TokenType::Newline || token->GetType() == TokenType::Comment || (token->GetType() == TokenType::SymbolBackslash)))
		{
			if (HasToken())
				token = std::move(m_Tokens[m_CurrentTokenIndex++]);
			else
				return {};
		}

		return token;
	}

	const Token* Parser::PeekToken()
	{
		if (!HasToken())
			return {};

		const Token* token = m_Tokens[m_CurrentTokenIndex].get();
		while (token && (token->GetType() == TokenType::Newline || token->GetType() == TokenType::Comment || (token->GetType() == TokenType::SymbolBackslash)))
		{
			if (HasToken())
				token = m_Tokens[++m_CurrentTokenIndex].get();
			else
				return {};
		}

		return token;
	}

	std::unique_ptr<Token> Parser::EatToken(TokenType type)
	{
		std::unique_ptr<Token> token = std::move(m_LookAhead);
		if (!token || token->GetType() != type)
			throw Error::Exceptions::SyntaxErrorException("Unexpected " + std::string(token->GetTypeString()), Error::ErrorType::ParserSyntaxError, token->GetSource());
		m_LookAhead = NextToken();
		return token;
	}
}
