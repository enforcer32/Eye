#include "Eye/Parser/Parser.h"
#include "Eye/Utility/Logger.h"
#include "Eye/Error/Exceptions/SyntaxErrorException.h"

namespace Eye
{
	std::expected<bool, Error::Error> Parser::Parse(const std::vector<std::shared_ptr<Token>>& tokens)
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
	std::vector<std::shared_ptr<AST::Statement>> Parser::StatementList(TokenType stopAt)
	{
		std::vector<std::shared_ptr<AST::Statement>> statementList;
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
	std::shared_ptr<AST::Statement> Parser::Statement()
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
	std::shared_ptr<AST::ExpressionStatement> Parser::ExpressionStatement()
	{
		if (IsLookAhead(TokenType::SymbolSemiColon))
		{
			EatToken(TokenType::SymbolSemiColon);
			return nullptr;
		}

		std::shared_ptr<AST::Expression> expression = Expression();
		EatToken(TokenType::SymbolSemiColon);
		return std::make_shared<AST::ExpressionStatement>(expression->GetSource(), expression);
	}

	/*
		BlockStatement
			: '{' OptionalStatementList '}'
			;
	*/
	std::shared_ptr<AST::BlockStatement> Parser::BlockStatement()
	{
		const auto& blockToken = EatToken(TokenType::SymbolLeftBrace);
		std::vector<std::shared_ptr<AST::Statement>> statementList;
		if (!IsLookAhead(TokenType::SymbolRightBrace))
			statementList = StatementList(TokenType::SymbolRightBrace);
		EatToken(TokenType::SymbolRightBrace);
		return std::make_shared<AST::BlockStatement>(blockToken->GetSource(), statementList);
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
	std::shared_ptr<AST::VariableStatement> Parser::VariableStatement()
	{
		std::shared_ptr<Token> typeQualifier;
		if (IsTypeQualifierKeyword(m_LookAhead))
			typeQualifier = EatToken(m_LookAhead->GetType());

		if (!IsDataTypeKeyword(m_LookAhead))
			throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		std::shared_ptr<Token> dataType = EatToken(m_LookAhead->GetType());
		const auto& varToken = (typeQualifier ? typeQualifier : dataType);
		std::shared_ptr<AST::VariableStatement> variableStatement = std::make_shared<AST::VariableStatement>(varToken->GetSource(), typeQualifier, dataType, VariableDeclarationList());
		EatToken(TokenType::SymbolSemiColon);
		return variableStatement;
	}

	/*
		VariableDeclarationList
			: VariableDeclaration
			| VariableDeclarationList ',' VariableDeclaration
			;
	*/
	std::vector<std::shared_ptr<AST::VariableDeclaration>> Parser::VariableDeclarationList()
	{
		std::vector<std::shared_ptr<AST::VariableDeclaration>> variableDeclarationList;
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
	std::shared_ptr<AST::VariableDeclaration> Parser::VariableDeclaration()
	{
		std::shared_ptr<AST::IdentifierExpression> identifier = IdentifierExpression();
		if (!IsLookAhead(TokenType::SymbolSemiColon) && !IsLookAhead(TokenType::OperatorComma))
			return std::make_shared<AST::VariableDeclaration>(identifier, VariableInitializer());
		return std::make_shared<AST::VariableDeclaration>(identifier, nullptr);
	}

	/*
		VariableInitializer
			: '=' AssignmentExpression
			;
	*/
	std::shared_ptr<AST::Expression> Parser::VariableInitializer()
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
	std::shared_ptr<AST::ControlStatement> Parser::ControlStatement()
	{
		const auto& ifToken = EatToken(TokenType::KeywordControlIf);
		EatToken(TokenType::OperatorLeftParenthesis);
		std::shared_ptr<AST::Expression> condition = Expression();
		if (!condition)
			throw Error::Exceptions::SyntaxErrorException("Expected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
		EatToken(TokenType::SymbolRightParenthesis);
		std::shared_ptr<AST::Statement> consequent = Statement();
		std::shared_ptr<AST::Statement> alternate = nullptr;
		if (IsLookAhead(TokenType::KeywordControlElse))
		{
			EatToken(TokenType::KeywordControlElse);
			alternate = Statement();
		}
		return std::make_shared<AST::ControlStatement>(ifToken->GetSource(), condition, consequent, alternate);
	}

	/*
		IterationStatement
			: WhileStatement
			| DoWhileStatement
			| ForStatement
			;
	*/
	std::shared_ptr<AST::IterationStatement> Parser::IterationStatement()
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
	std::shared_ptr<AST::ContinueStatement> Parser::ContinueStatement()
	{
		const auto& continueToken = EatToken(TokenType::KeywordIterationContinue);
		EatToken(TokenType::SymbolSemiColon);
		return std::make_shared<AST::ContinueStatement>(continueToken->GetSource());
	}

	/*
		BreakStatement
			: 'break' ';'
			;
	*/
	std::shared_ptr<AST::BreakStatement> Parser::BreakStatement()
	{
		const auto& breakToken = EatToken(TokenType::KeywordIterationBreak);
		EatToken(TokenType::SymbolSemiColon);
		return std::make_shared<AST::BreakStatement>(breakToken->GetSource());
	}

	/*
		WhileStatement
			: 'while' '(' Expression ')' Statement
			;
	*/
	std::shared_ptr<AST::WhileStatement> Parser::WhileStatement()
	{
		const auto& whileToken = EatToken(TokenType::KeywordIterationWhile);
		EatToken(TokenType::OperatorLeftParenthesis);
		std::shared_ptr<AST::Expression> condition = Expression();
		if (!condition)
			throw Error::Exceptions::SyntaxErrorException("Expected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
		EatToken(TokenType::SymbolRightParenthesis);
		std::shared_ptr<AST::Statement> body = Statement();
		return std::make_shared<AST::WhileStatement>(whileToken->GetSource(), condition, body);
	}

	/*
		DoWhileStatement
			: 'do' Statement 'while' '(' Expression ')' ';'
			;
	*/
	std::shared_ptr<AST::DoWhileStatement> Parser::DoWhileStatement()
	{
		const auto& doToken = EatToken(TokenType::KeywordIterationDo);
		std::shared_ptr<AST::Statement> body = Statement();
		EatToken(TokenType::KeywordIterationWhile);
		EatToken(TokenType::OperatorLeftParenthesis);
		std::shared_ptr<AST::Expression> condition = Expression();
		if (!condition)
			throw Error::Exceptions::SyntaxErrorException("Expected Expression", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());
		EatToken(TokenType::SymbolRightParenthesis);
		EatToken(TokenType::SymbolSemiColon);
		return std::make_shared<AST::DoWhileStatement>(doToken->GetSource(), condition, body);
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
	std::shared_ptr<AST::ForStatement> Parser::ForStatement()
	{
		const auto& forToken = EatToken(TokenType::KeywordIterationFor);
		EatToken(TokenType::OperatorLeftParenthesis);

		std::shared_ptr<void> initializer = nullptr;
		AST::ForInitializerType initializerType = AST::ForInitializerType::Null;
		if (!IsLookAhead(TokenType::SymbolSemiColon))
		{
			if (IsTypeQualifierKeyword(m_LookAhead) || IsDataTypeKeyword(m_LookAhead))
			{
				std::shared_ptr<Token> typeQualifier;
				if (IsTypeQualifierKeyword(m_LookAhead))
					typeQualifier = EatToken(m_LookAhead->GetType());

				if (!IsDataTypeKeyword(m_LookAhead))
					throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

				std::shared_ptr<Token> dataType = EatToken(m_LookAhead->GetType());
				const auto& varToken = (typeQualifier ? typeQualifier : dataType);
				initializer = std::make_shared<AST::VariableStatement>(varToken->GetSource(), typeQualifier, dataType, VariableDeclarationList());
				initializerType = AST::ForInitializerType::VariableStatement;
			}
			else
			{
				initializer = Expression();
				initializerType = AST::ForInitializerType::Expression;
			}
		}
		EatToken(TokenType::SymbolSemiColon);

		std::shared_ptr<AST::Expression> condition = (IsLookAhead(TokenType::SymbolSemiColon) ? nullptr : Expression());
		EatToken(TokenType::SymbolSemiColon);

		std::shared_ptr<AST::Expression> update = (IsLookAhead(TokenType::SymbolRightParenthesis) ? nullptr : Expression());
		EatToken(TokenType::SymbolRightParenthesis);

		std::shared_ptr<AST::Statement> body = Statement();
		return std::make_shared<AST::ForStatement>(forToken->GetSource(), initializer, initializerType, condition, update, body);
	}

	/*
		FunctionStatement
			: 'function' DataTypeKeyword Identifier '(' OptionalFunctionParameterList ')' BlockStatement
			;
	*/
	std::shared_ptr<AST::FunctionStatement> Parser::FunctionStatement()
	{
		const auto& functionToken = EatToken(TokenType::KeywordFunction);

		if (!IsDataTypeKeyword(m_LookAhead))
			throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		std::shared_ptr<Token> returnType = EatToken(m_LookAhead->GetType());
		std::shared_ptr<AST::IdentifierExpression> identifier = IdentifierExpression();

		EatToken(TokenType::OperatorLeftParenthesis);
		std::vector<std::shared_ptr<AST::FunctionParameter>> parameters;
		if (!IsLookAhead(TokenType::SymbolRightParenthesis))
			parameters = FunctionParameterList();
		EatToken(TokenType::SymbolRightParenthesis);

		std::shared_ptr<AST::BlockStatement> body = BlockStatement();
		return std::make_shared<AST::FunctionStatement>(functionToken->GetSource(), returnType, identifier, parameters, body);
	}

	/*
		FunctionParameterList
			: FunctionParameter
			| FunctionParameterList ',' FunctionParameter
			;
	*/
	std::vector<std::shared_ptr<AST::FunctionParameter>> Parser::FunctionParameterList()
	{
		std::vector<std::shared_ptr<AST::FunctionParameter>> parameters;
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
	std::shared_ptr<AST::FunctionParameter> Parser::FunctionParameter()
	{
		std::shared_ptr<Token> typeQualifier;
		if (IsTypeQualifierKeyword(m_LookAhead))
			typeQualifier = EatToken(m_LookAhead->GetType());

		if (!IsDataTypeKeyword(m_LookAhead))
			throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		std::shared_ptr<Token> dataType = EatToken(m_LookAhead->GetType());
		std::shared_ptr<AST::IdentifierExpression> identifier = IdentifierExpression();
		if (!IsLookAhead(TokenType::SymbolRightParenthesis) && !IsLookAhead(TokenType::OperatorComma))
			return std::make_shared<AST::FunctionParameter>(typeQualifier, dataType, identifier, VariableInitializer());
		return std::make_shared<AST::FunctionParameter>(typeQualifier, dataType, identifier, nullptr);
	}

	/*
		ReturnStatement
			: 'return' OptionalExpression ';'
			;
	*/
	std::shared_ptr<AST::ReturnStatement> Parser::ReturnStatement()
	{
		const auto& returnToken = EatToken(TokenType::KeywordReturn);
		std::shared_ptr<AST::Expression> expression = (!IsLookAhead(TokenType::SymbolSemiColon)) ? Expression() : nullptr;
		EatToken(TokenType::SymbolSemiColon);
		return std::make_shared<AST::ReturnStatement>(returnToken->GetSource(), expression);
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
			throw Error::Exceptions::SyntaxErrorException("Unexpected LHSExpression '" + m_LookAhead->GetValueString() + "'", Error::ErrorType::ParserSyntaxError, m_LookAhead->GetSource());

		std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
		return std::make_shared<AST::AssignmentExpression>(op->GetSource(), op, left, AssignmentExpression());
	}

	/*
		LogicalORExpression
			: LogicalANDExpression '||' LogicalORExpression
			| LogicalANDExpression
			;
	*/
	std::shared_ptr<AST::Expression> Parser::LogicalORExpression()
	{
		std::shared_ptr<AST::Expression> left = LogicalANDExpression();
		while (IsLookAhead(TokenType::OperatorLogicalOR))
		{
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::Expression> right = LogicalANDExpression();
			left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		LogicalANDExpression
			: BitwiseORExpression '&&' LogicalANDExpression
			| BitwiseORExpression
			;
	*/
	std::shared_ptr<AST::Expression> Parser::LogicalANDExpression()
	{
		std::shared_ptr<AST::Expression> left = BitwiseORExpression();
		while (IsLookAhead(TokenType::OperatorLogicalAND))
		{
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::Expression> right = BitwiseORExpression();
			left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		BitwiseORExpression
			: BitwiseXORExpression '|' BitwiseORExpression
			| BitwiseXORExpression
			;
	*/
	std::shared_ptr<AST::Expression> Parser::BitwiseORExpression()
	{
		std::shared_ptr<AST::Expression> left = BitwiseXORExpression();
		while (IsLookAhead(TokenType::OperatorBitwiseBinaryOR))
		{
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::Expression> right = BitwiseXORExpression();
			left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		BitwiseXORExpression
			: BitwiseANDExpression '|' BitwiseXORExpression
			| BitwiseANDExpression
			;
	*/
	std::shared_ptr<AST::Expression> Parser::BitwiseXORExpression()
	{
		std::shared_ptr<AST::Expression> left = BitwiseANDExpression();
		while (IsLookAhead(TokenType::OperatorBitwiseBinaryXOR))
		{
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::Expression> right = BitwiseANDExpression();
			left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		BitwiseANDExpression
			: EqualityExpression '&' BitwiseANDExpression
			| EqualityExpression
			;
	*/
	std::shared_ptr<AST::Expression> Parser::BitwiseANDExpression()
	{
		std::shared_ptr<AST::Expression> left = EqualityExpression();
		while (IsLookAhead(TokenType::OperatorBitwiseBinaryAND))
		{
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::Expression> right = EqualityExpression();
			left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
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
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::Expression> right = RelationalExpression();
			left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		RelationalExpression
			: BitwiseShiftExpression
			| BitwiseShiftExpression RelationalOperator RelationalExpression
			;
	*/
	std::shared_ptr<AST::Expression> Parser::RelationalExpression()
	{
		std::shared_ptr<AST::Expression> left = BitwiseShiftExpression();
		while (IsRelationalOperator(m_LookAhead))
		{
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::Expression> right = BitwiseShiftExpression();
			left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
		}
		return left;
	}

	/*
		BitwiseShiftExpression
			: AdditiveBinaryExpression
			| AdditiveBinaryExpression BitwiseShiftOperator BitwiseShiftExpression
			;
	*/
	std::shared_ptr<AST::Expression> Parser::BitwiseShiftExpression()
	{
		std::shared_ptr<AST::Expression> left = AdditiveBinaryExpression();
		while (IsBitwiseShiftOperator(m_LookAhead))
		{
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::Expression> right = AdditiveBinaryExpression();
			left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
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
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::Expression> right = MultiplicativeBinaryExpression();
			left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
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
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::Expression> right = UnaryExpression();
			left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
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
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			return std::make_shared<AST::UnaryExpression>(op->GetSource(), op, UnaryExpression());
		}

		return LHSExpression();
	}

	/*
		LHSExpression
			: MemberExpression
			| CallExpression
			;
	*/
	std::shared_ptr<AST::Expression> Parser::LHSExpression()
	{
		std::shared_ptr<AST::Expression> memberExpression = MemberExpression();
		if (IsLookAhead(TokenType::OperatorLeftParenthesis))
			return CallExpression(memberExpression);
		return memberExpression;
	}

	/*
		MemberExpression
			: PostfixExpression
			| MemberExpression '.' Identifier
			| MemberExpression '[' Expression ']'
	*/
	std::shared_ptr<AST::Expression> Parser::MemberExpression()
	{
		std::shared_ptr<AST::Expression> obj = PostfixExpression();
		while (IsLookAhead(TokenType::OperatorDot) || IsLookAhead(TokenType::OperatorLeftBracket))
		{
			if (IsLookAhead(TokenType::OperatorDot))
			{
				const auto& op = EatToken(TokenType::OperatorDot);
				std::shared_ptr<AST::IdentifierExpression> prop = IdentifierExpression();
				obj = std::make_shared<AST::MemberExpression>(op->GetSource(), obj, prop, false);
			}
			else if (IsLookAhead(TokenType::OperatorLeftBracket))
			{
				const auto& op = EatToken(TokenType::OperatorLeftBracket);
				std::shared_ptr<AST::Expression> prop = Expression();
				EatToken(TokenType::SymbolRightBracket);
				obj = std::make_shared<AST::MemberExpression>(op->GetSource(), obj, prop, true);
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
	std::shared_ptr<AST::Expression> Parser::CallExpression(const std::shared_ptr<AST::Expression>& callee)
	{
		std::shared_ptr<AST::Expression> callExpression = std::make_shared<AST::CallExpression>(m_LookAhead->GetSource(), callee, CallArguments());
		if (IsLookAhead(TokenType::OperatorLeftParenthesis))
			callExpression = CallExpression(callExpression);
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
	std::vector<std::shared_ptr<AST::Expression>> Parser::CallArguments()
	{
		EatToken(TokenType::OperatorLeftParenthesis);
		std::vector<std::shared_ptr<AST::Expression>> arguments;
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
	std::shared_ptr<AST::Expression> Parser::PostfixExpression()
	{
		std::shared_ptr<AST::Expression> primaryExpression = PrimaryExpression();
		if (IsPostfixOperator(m_LookAhead))
		{
			std::shared_ptr<Token> op = EatToken(m_LookAhead->GetType());
			return std::make_shared<AST::PostfixExpression>(op->GetSource(), op, primaryExpression);
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
	std::shared_ptr<AST::Expression> Parser::PrimaryExpression()
	{
		if (IsLiteral(m_LookAhead))
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
	std::shared_ptr<AST::LiteralExpression> Parser::LiteralExpression()
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
	std::shared_ptr<AST::LiteralExpression> Parser::IntegerLiteral()
	{
		std::shared_ptr<Token> token = EatToken(TokenType::LiteralInteger);
		return std::make_shared<AST::LiteralExpression>(token->GetSource(), (AST::LiteralIntegerType)token->GetValue<IntegerType>());
	}

	/*
		FloatLiteral
			: FLOAT
			;
	*/
	std::shared_ptr<AST::LiteralExpression> Parser::FloatLiteral()
	{
		std::shared_ptr<Token> token = EatToken(TokenType::LiteralFloat);
		return std::make_shared<AST::LiteralExpression>(token->GetSource(), (AST::LiteralFloatType)token->GetValue<FloatType>());
	}

	/*
		StringLiteral
			: STRING
			;
	*/
	std::shared_ptr<AST::LiteralExpression> Parser::StringLiteral()
	{
		std::shared_ptr<Token> token = EatToken(TokenType::LiteralString);
		return std::make_shared<AST::LiteralExpression>(token->GetSource(), (AST::LiteralStringType)token->GetValue<StringType>());
	}

	/*
		BooleanLiteral
			: BOOL
			;
	*/
	std::shared_ptr<AST::LiteralExpression> Parser::BooleanLiteral()
	{
		std::shared_ptr<Token> token = EatToken(TokenType::LiteralBoolean);
		return std::make_shared<AST::LiteralExpression>(token->GetSource(), (AST::LiteralBooleanType)token->GetValue<BooleanType>());
	}

	/*
		NullLiteral
			: NULL
			;
	*/
	std::shared_ptr<AST::LiteralExpression> Parser::NullLiteral()
	{
		std::shared_ptr<Token> token = EatToken(TokenType::LiteralNull);
		return std::make_shared<AST::LiteralExpression>(token->GetSource(), AST::LiteralType::Null);
	}

	/*
		ParenthesizedExpression
			: '(' Expression ')'
			;
	*/
	std::shared_ptr<AST::Expression> Parser::ParenthesizedExpression()
	{
		EatToken(TokenType::OperatorLeftParenthesis);
		std::shared_ptr<AST::Expression> expression = Expression();
		EatToken(TokenType::SymbolRightParenthesis);
		return expression;
	}

	/*
		IdentifierExpression
			: IdentifierToken
			;
	*/
	std::shared_ptr<AST::IdentifierExpression> Parser::IdentifierExpression()
	{
		const auto& id = EatToken(TokenType::Identifier);
		return std::make_shared<AST::IdentifierExpression>(id->GetSource(), id);
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
	bool Parser::IsLiteral(const std::shared_ptr<Token>& token) const
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
			| '|='				| '^='
			| '>>='
			| '<<='
			;
	*/
	bool Parser::IsAssignmentOperator(const std::shared_ptr<Token>& token) const
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
	bool Parser::IsEqualityOperator(const std::shared_ptr<Token>& token) const
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
	bool Parser::IsRelationalOperator(const std::shared_ptr<Token>& token) const
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
	bool Parser::IsBitwiseShiftOperator(const std::shared_ptr<Token>& token) const
	{
		return (token->GetType() == TokenType::OperatorBitwiseLeftShift || token->GetType() == TokenType::OperatorBitwiseRightShift);
	}

	/*
		AdditiveOperator
			: '+'
			| '-'
			;
	*/
	bool Parser::IsAdditiveOperator(const std::shared_ptr<Token>& token) const
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
	bool Parser::IsMultiplicativeOperator(const std::shared_ptr<Token>& token) const
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
	bool Parser::IsUnaryOperator(const std::shared_ptr<Token>& token) const
	{
		return (token->GetType() == TokenType::OperatorBinaryPlus || token->GetType() == TokenType::OperatorBinaryMinus || token->GetType() == TokenType::OperatorLogicalNOT || token->GetType() == TokenType::OperatorArithmeticIncrement || token->GetType() == TokenType::OperatorArithmeticDecrement || token->GetType() == TokenType::OperatorBitwiseNOT);
	}

	/*
		PostfixOperator
			: '++'
			| '--'
			;
	*/
	bool Parser::IsPostfixOperator(const std::shared_ptr<Token>& token) const
	{
		return (token->GetType() == TokenType::OperatorArithmeticIncrement || token->GetType() == TokenType::OperatorArithmeticDecrement);
	}

	/*
		TypeQualifier
			: 'const'
			;
	*/
	bool Parser::IsTypeQualifierKeyword(const std::shared_ptr<Token>& token) const
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
	bool Parser::IsDataTypeKeyword(const std::shared_ptr<Token>& token) const
	{
		return (token->GetType() == TokenType::KeywordDataTypeInt || token->GetType() == TokenType::KeywordDataTypeFloat || token->GetType() == TokenType::KeywordDataTypeStr || token->GetType() == TokenType::KeywordDataTypeBool || token->GetType() == TokenType::KeywordDataTypeVoid);
	}

	/*
		LHSExpression
			: IdentifierExpression
			;
	*/
	bool Parser::IsLHSExpression(const std::shared_ptr<AST::Expression>& expression) const
	{
		return (expression->GetType() == AST::ExpressionType::IdentifierExpression || expression->GetType() == AST::ExpressionType::MemberExpression);
	}

	bool Parser::HasToken() const
	{
		return m_CurrentTokenIndex < m_Tokens.size();
	}

	std::shared_ptr<Token> Parser::NextToken()
	{
		if (!HasToken())
			return {};

		std::shared_ptr<Token> token = m_Tokens[m_CurrentTokenIndex++];
		while (token && (token->GetType() == TokenType::Newline || token->GetType() == TokenType::Comment || (token->GetType() == TokenType::SymbolBackslash)))
		{
			if (HasToken())
				token = m_Tokens[m_CurrentTokenIndex++];
			else
				return {};
		}

		return token;
	}

	std::shared_ptr<Token> Parser::PeekToken()
	{
		if (!HasToken())
			return {};

		std::shared_ptr<Token> token = m_Tokens[m_CurrentTokenIndex];
		while (token && (token->GetType() == TokenType::Newline || token->GetType() == TokenType::Comment || (token->GetType() == TokenType::SymbolBackslash)))
		{
			if (HasToken())
				token = m_Tokens[++m_CurrentTokenIndex];
			else
				return {};
		}

		return token;
	}

	std::shared_ptr<Token> Parser::EatToken(TokenType type)
	{
		std::shared_ptr<Token> token = m_LookAhead;
		if (!token || token->GetType() != type)
			throw Error::Exceptions::SyntaxErrorException("Unexpected " + std::string(token->GetTypeString()), Error::ErrorType::ParserSyntaxError, token->GetSource());
		m_LookAhead = NextToken();
		return token;
	}
}
