#include "EYEParser/Parser.h"

#include <EYEUtility/Logger.h>
#include <EYEError/Exceptions/SyntaxErrorException.h>

namespace Eye
{
	namespace Parser
	{
		std::expected<bool, Error::Error> Parser::Parse(const std::vector<std::shared_ptr<Lexer::Token>>& tokens)
		{
			m_Tokens = tokens;
			m_CurrentTokenIndex = 0;

			try
			{
				m_LookAhead = NextToken();
				m_Program = Program();
			}
			catch (const Error::Exceptions::SyntaxErrorException& ex)
			{
				return std::unexpected(Error::Error(Error::ErrorType::ParserSyntaxError, ex.what()));
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
		std::vector<std::shared_ptr<AST::Statement>> Parser::StatementList(Lexer::TokenType stopAt)
		{
			std::vector<std::shared_ptr<AST::Statement>> statementList;
			while (m_LookAhead && m_LookAhead->GetType() != Lexer::TokenType::EndOfFile && m_LookAhead->GetType() != stopAt)
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
			case Lexer::TokenType::SymbolLeftBrace:
				return BlockStatement();
			case Lexer::TokenType::KeywordTypeQualifierConst:
			case Lexer::TokenType::KeywordDataTypeInt:
			case Lexer::TokenType::KeywordDataTypeFloat:
			case Lexer::TokenType::KeywordDataTypeStr:
			case Lexer::TokenType::KeywordDataTypeBool:
			case Lexer::TokenType::KeywordDataTypeVoid:
				return VariableStatement();
			case Lexer::TokenType::KeywordControlIf:
				return ControlStatement();
			case Lexer::TokenType::KeywordIterationWhile:
			case Lexer::TokenType::KeywordIterationDo:
			case Lexer::TokenType::KeywordIterationFor:
				return IterationStatement();
			case Lexer::TokenType::KeywordIterationContinue:
				return ContinueStatement();
			case Lexer::TokenType::KeywordIterationBreak:
				return BreakStatement();
			case Lexer::TokenType::KeywordFunction:
				return FunctionStatement();
			case Lexer::TokenType::KeywordReturn:
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
			if (IsLookAhead(Lexer::TokenType::SymbolSemiColon))
			{
				EatToken(Lexer::TokenType::SymbolSemiColon);
				return nullptr;
			}

			std::shared_ptr<AST::Expression> expression = Expression();
			EatToken(Lexer::TokenType::SymbolSemiColon);
			return std::make_shared<AST::ExpressionStatement>(expression->GetSource(), expression);
		}

		/*
			BlockStatement
				: '{' OptionalStatementList '}'
				;
		*/
		std::shared_ptr<AST::BlockStatement> Parser::BlockStatement()
		{
			const auto& blockToken = EatToken(Lexer::TokenType::SymbolLeftBrace);
			std::vector<std::shared_ptr<AST::Statement>> statementList;
			if (!IsLookAhead(Lexer::TokenType::SymbolRightBrace))
				statementList = StatementList(Lexer::TokenType::SymbolRightBrace);
			EatToken(Lexer::TokenType::SymbolRightBrace);
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
			std::shared_ptr<Lexer::Token> typeQualifier;
			if (IsTypeQualifierKeyword(m_LookAhead))
				typeQualifier = EatToken(m_LookAhead->GetType());

			if (!IsDataTypeKeyword(m_LookAhead))
				throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", m_LookAhead->GetSource());
			
			std::shared_ptr<Lexer::Token> dataType = EatToken(m_LookAhead->GetType());
			const auto& varToken = (typeQualifier ? typeQualifier : dataType);
			std::shared_ptr<AST::VariableStatement> variableStatement = std::make_shared<AST::VariableStatement>(varToken->GetSource(), typeQualifier, dataType, VariableDeclarationList());
			EatToken(Lexer::TokenType::SymbolSemiColon);
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
			} while (IsLookAhead(Lexer::TokenType::OperatorComma) && EatToken(Lexer::TokenType::OperatorComma));
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
			if (!IsLookAhead(Lexer::TokenType::SymbolSemiColon) && !IsLookAhead(Lexer::TokenType::OperatorComma))
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
			EatToken(Lexer::TokenType::OperatorAssignment);
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
			const auto& ifToken = EatToken(Lexer::TokenType::KeywordControlIf);
			EatToken(Lexer::TokenType::OperatorLeftParenthesis);
			std::shared_ptr<AST::Expression> condition = Expression();
			if(!condition)
				throw Error::Exceptions::SyntaxErrorException("Expected Expression", m_LookAhead->GetSource());
			EatToken(Lexer::TokenType::SymbolRightParenthesis);
			std::shared_ptr<AST::Statement> consequent = Statement();
			std::shared_ptr<AST::Statement> alternate = nullptr;
			if (IsLookAhead(Lexer::TokenType::KeywordControlElse))
			{
				EatToken(Lexer::TokenType::KeywordControlElse);
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
			if (IsLookAhead(Lexer::TokenType::KeywordIterationWhile))
				return WhileStatement();
			else if (IsLookAhead(Lexer::TokenType::KeywordIterationDo))
				return DoWhileStatement();
			else if (IsLookAhead(Lexer::TokenType::KeywordIterationFor))
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
			const auto& continueToken = EatToken(Lexer::TokenType::KeywordIterationContinue);
			EatToken(Lexer::TokenType::SymbolSemiColon);
			return std::make_shared<AST::ContinueStatement>(continueToken->GetSource());
		}
	
		/*
			BreakStatement
				: 'break' ';'
				;
		*/
		std::shared_ptr<AST::BreakStatement> Parser::BreakStatement()
		{
			const auto& breakToken = EatToken(Lexer::TokenType::KeywordIterationBreak);
			EatToken(Lexer::TokenType::SymbolSemiColon);
			return std::make_shared<AST::BreakStatement>(breakToken->GetSource());
		}

		/*
			WhileStatement
				: 'while' '(' Expression ')' Statement
				;
		*/
		std::shared_ptr<AST::WhileStatement> Parser::WhileStatement()
		{
			const auto& whileToken = EatToken(Lexer::TokenType::KeywordIterationWhile);
			EatToken(Lexer::TokenType::OperatorLeftParenthesis);
			std::shared_ptr<AST::Expression> condition = Expression();
			if(!condition)
				throw Error::Exceptions::SyntaxErrorException("Expected Expression", m_LookAhead->GetSource());
			EatToken(Lexer::TokenType::SymbolRightParenthesis);
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
			const auto& doToken = EatToken(Lexer::TokenType::KeywordIterationDo);
			std::shared_ptr<AST::Statement> body = Statement();
			EatToken(Lexer::TokenType::KeywordIterationWhile);
			EatToken(Lexer::TokenType::OperatorLeftParenthesis);
			std::shared_ptr<AST::Expression> condition = Expression();
			if (!condition)
				throw Error::Exceptions::SyntaxErrorException("Expected Expression", m_LookAhead->GetSource());
			EatToken(Lexer::TokenType::SymbolRightParenthesis);
			EatToken(Lexer::TokenType::SymbolSemiColon);
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
			const auto& forToken = EatToken(Lexer::TokenType::KeywordIterationFor);
			EatToken(Lexer::TokenType::OperatorLeftParenthesis);

			std::shared_ptr<void> initializer = nullptr;
			AST::ForInitializerType initializerType = AST::ForInitializerType::Null;
			if (!IsLookAhead(Lexer::TokenType::SymbolSemiColon))
			{
				if (IsTypeQualifierKeyword(m_LookAhead) || IsDataTypeKeyword(m_LookAhead))
				{
					std::shared_ptr<Lexer::Token> typeQualifier;
					if (IsTypeQualifierKeyword(m_LookAhead))
						typeQualifier = EatToken(m_LookAhead->GetType());

					if (!IsDataTypeKeyword(m_LookAhead))
						throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", m_LookAhead->GetSource());

					std::shared_ptr<Lexer::Token> dataType = EatToken(m_LookAhead->GetType());
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
			EatToken(Lexer::TokenType::SymbolSemiColon);

			std::shared_ptr<AST::Expression> condition = (IsLookAhead(Lexer::TokenType::SymbolSemiColon) ? nullptr : Expression());
			EatToken(Lexer::TokenType::SymbolSemiColon);

			std::shared_ptr<AST::Expression> update = (IsLookAhead(Lexer::TokenType::SymbolRightParenthesis) ? nullptr : Expression());
			EatToken(Lexer::TokenType::SymbolRightParenthesis);

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
			const auto& functionToken = EatToken(Lexer::TokenType::KeywordFunction);
			
			if (!IsDataTypeKeyword(m_LookAhead))
				throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", m_LookAhead->GetSource());

			std::shared_ptr<Lexer::Token> returnType = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::IdentifierExpression> identifier = IdentifierExpression();

			EatToken(Lexer::TokenType::OperatorLeftParenthesis);
			std::vector<std::shared_ptr<AST::FunctionParameter>> parameters;
			if (!IsLookAhead(Lexer::TokenType::SymbolRightParenthesis))
				parameters = FunctionParameterList();
			EatToken(Lexer::TokenType::SymbolRightParenthesis);

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
			} while (IsLookAhead(Lexer::TokenType::OperatorComma) && EatToken(Lexer::TokenType::OperatorComma));
			return parameters;
		}

		/*
			FunctionParameter
				: OptionalTypeQualifierKeyword DataTypeKeyword IdentifierExpression OptionalVariableInitializer
				;
		*/
		std::shared_ptr<AST::FunctionParameter> Parser::FunctionParameter()
		{
			std::shared_ptr<Lexer::Token> typeQualifier;
			if (IsTypeQualifierKeyword(m_LookAhead))
				typeQualifier = EatToken(m_LookAhead->GetType());

			if (!IsDataTypeKeyword(m_LookAhead))
				throw Error::Exceptions::SyntaxErrorException("Unexpected Datatype '" + m_LookAhead->GetValueString() + "'", m_LookAhead->GetSource());

			std::shared_ptr<Lexer::Token> dataType = EatToken(m_LookAhead->GetType());
			std::shared_ptr<AST::IdentifierExpression> identifier = IdentifierExpression();
			if (!IsLookAhead(Lexer::TokenType::SymbolRightParenthesis) && !IsLookAhead(Lexer::TokenType::OperatorComma))
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
			const auto& returnToken = EatToken(Lexer::TokenType::KeywordReturn);
			std::shared_ptr<AST::Expression> expression = (!IsLookAhead(Lexer::TokenType::SymbolSemiColon)) ? Expression() : nullptr;
			EatToken(Lexer::TokenType::SymbolSemiColon);
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
				throw Error::Exceptions::SyntaxErrorException("Unexpected LHSExpression '" + m_LookAhead->GetValueString() + "'", m_LookAhead->GetSource());

			std::shared_ptr<Lexer::Token> op = EatToken(m_LookAhead->GetType());
			return std::make_shared<AST::AssignmentExpression>(op->GetSource(), op, left, AssignmentExpression());
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
				std::shared_ptr<Lexer::Token> op = EatToken(m_LookAhead->GetType());
				std::shared_ptr<AST::Expression> right = LogicalANDExpression();
				left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
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
				std::shared_ptr<Lexer::Token> op = EatToken(m_LookAhead->GetType());
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
				std::shared_ptr<Lexer::Token> op = EatToken(m_LookAhead->GetType());
				std::shared_ptr<AST::Expression> right = RelationalExpression();
				left = std::make_shared<AST::BinaryExpression>(op->GetSource(), op, left, right);
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
				std::shared_ptr<Lexer::Token> op = EatToken(m_LookAhead->GetType());
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
				std::shared_ptr<Lexer::Token> op = EatToken(m_LookAhead->GetType());
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
				std::shared_ptr<Lexer::Token> op = EatToken(m_LookAhead->GetType());
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
				std::shared_ptr<Lexer::Token> op = EatToken(m_LookAhead->GetType());
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
			if (IsLookAhead(Lexer::TokenType::OperatorLeftParenthesis))
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
			while (IsLookAhead(Lexer::TokenType::OperatorDot) || IsLookAhead(Lexer::TokenType::OperatorLeftBracket))
			{
				if (IsLookAhead(Lexer::TokenType::OperatorDot))
				{
					const auto& op = EatToken(Lexer::TokenType::OperatorDot);
					std::shared_ptr<AST::IdentifierExpression> prop = IdentifierExpression();
					obj = std::make_shared<AST::MemberExpression>(op->GetSource(), obj, prop, false);
				}
				else if (IsLookAhead(Lexer::TokenType::OperatorLeftBracket))
				{
					const auto& op = EatToken(Lexer::TokenType::OperatorLeftBracket);
					std::shared_ptr<AST::Expression> prop = Expression();
					EatToken(Lexer::TokenType::SymbolRightBracket);
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
			if (IsLookAhead(Lexer::TokenType::OperatorLeftParenthesis))
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
			EatToken(Lexer::TokenType::OperatorLeftParenthesis);
			std::vector<std::shared_ptr<AST::Expression>> arguments;
			if (!IsLookAhead(Lexer::TokenType::SymbolRightParenthesis))
			{
				do
				{
					arguments.push_back(AssignmentExpression());
				} while (IsLookAhead(Lexer::TokenType::OperatorComma) && EatToken(Lexer::TokenType::OperatorComma));
			}
			EatToken(Lexer::TokenType::SymbolRightParenthesis);
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
				std::shared_ptr<Lexer::Token> op = EatToken(m_LookAhead->GetType());
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
			switch (m_LookAhead->GetType())
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
				throw Error::Exceptions::SyntaxErrorException("Unexpected LiteralExpression '" + m_LookAhead->GetValueString() + "'", m_LookAhead->GetSource());
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
			std::shared_ptr<Lexer::Token> token = EatToken(Lexer::TokenType::LiteralInteger);
			return std::make_shared<AST::LiteralExpression>(token->GetSource(), (AST::LiteralIntegerType)token->GetValue<Lexer::IntegerType>());
		}

		/*
			FloatLiteral
				: FLOAT
				;
		*/
		std::shared_ptr<AST::LiteralExpression> Parser::FloatLiteral()
		{
			std::shared_ptr<Lexer::Token> token = EatToken(Lexer::TokenType::LiteralFloat);
			return std::make_shared<AST::LiteralExpression>(token->GetSource(), (AST::LiteralFloatType)token->GetValue<Lexer::FloatType>());
		}
		
		/*
			StringLiteral
				: STRING
				;
		*/
		std::shared_ptr<AST::LiteralExpression> Parser::StringLiteral()
		{
			std::shared_ptr<Lexer::Token> token = EatToken(Lexer::TokenType::LiteralString);
			return std::make_shared<AST::LiteralExpression>(token->GetSource(), (AST::LiteralStringType)token->GetValue<Lexer::StringType>());
		}
		
		/*
			BooleanLiteral
				: BOOL
				;
		*/
		std::shared_ptr<AST::LiteralExpression> Parser::BooleanLiteral()
		{
			std::shared_ptr<Lexer::Token> token = EatToken(Lexer::TokenType::LiteralBoolean);
			return std::make_shared<AST::LiteralExpression>(token->GetSource(), (AST::LiteralBooleanType)token->GetValue<Lexer::BooleanType>());
		}
		
		/*
			NullLiteral
				: NULL
				;
		*/
		std::shared_ptr<AST::LiteralExpression> Parser::NullLiteral()
		{
			std::shared_ptr<Lexer::Token> token = EatToken(Lexer::TokenType::LiteralNull);
			return std::make_shared<AST::LiteralExpression>(token->GetSource(), AST::LiteralType::Null);
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
			const auto& id = EatToken(Lexer::TokenType::Identifier);
			return std::make_shared<AST::IdentifierExpression>(id->GetSource(), id);
		}

		bool Parser::IsLookAhead(Lexer::TokenType type) const
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
		bool Parser::IsLiteral(const std::shared_ptr<Lexer::Token>& token) const
		{
			return (token->GetType() == Lexer::TokenType::LiteralInteger || token->GetType() == Lexer::TokenType::LiteralFloat || token->GetType() == Lexer::TokenType::LiteralString || token->GetType() == Lexer::TokenType::LiteralBoolean || token->GetType() == Lexer::TokenType::LiteralNull);
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
		bool Parser::IsAssignmentOperator(const std::shared_ptr<Lexer::Token>& token) const
		{
			return (token->GetType() == Lexer::TokenType::OperatorAssignment || token->GetType() == Lexer::TokenType::OperatorAssignmentPlus || token->GetType() == Lexer::TokenType::OperatorAssignmentMinus ||
				token->GetType() == Lexer::TokenType::OperatorAssignmentStar || token->GetType() == Lexer::TokenType::OperatorAssignmentSlash || token->GetType() == Lexer::TokenType::OperatorAssignmentModulo ||
				token->GetType() == Lexer::TokenType::OperatorAssignmentBitwiseAND || token->GetType() == Lexer::TokenType::OperatorAssignmentBitwiseOR || token->GetType() == Lexer::TokenType::OperatorAssignmentBitwiseXOR
				|| token->GetType() == Lexer::TokenType::OperatorAssignmentBitwiseLeftShift || token->GetType() == Lexer::TokenType::OperatorAssignmentBitwiseRightShift || token->GetType() == Lexer::TokenType::OperatorAssignmentBitwiseXOR);
		}

		/*
			EqualityOperator
				: '=='
				| '!=
				;
		*/
		bool Parser::IsEqualityOperator(const std::shared_ptr<Lexer::Token>& token) const
		{
			return (token->GetType() == Lexer::TokenType::OperatorRelationalEquals || token->GetType() == Lexer::TokenType::OperatorRelationalNotEquals);
		}

		/*
			RelationalOperator
				: '<'
				| '<='
				| '>'
				| '>='
				;
		*/
		bool Parser::IsRelationalOperator(const std::shared_ptr<Lexer::Token>& token) const
		{
			return (token->GetType() == Lexer::TokenType::OperatorRelationalSmaller || token->GetType() == Lexer::TokenType::OperatorRelationalSmallerEquals || token->GetType() == Lexer::TokenType::OperatorRelationalGreater ||
				token->GetType() == Lexer::TokenType::OperatorRelationalGreaterEquals);
		}

		/*
			AdditiveOperator
				: '+'
				| '-'
				;
		*/
		bool Parser::IsAdditiveOperator(const std::shared_ptr<Lexer::Token>& token) const
		{
			return (token->GetType() == Lexer::TokenType::OperatorBinaryPlus || token->GetType() == Lexer::TokenType::OperatorBinaryMinus);
		}

		/*
			MultiplicativeOperator
				: '*'
				| '/'
				| '%'
				;
		*/
		bool Parser::IsMultiplicativeOperator(const std::shared_ptr<Lexer::Token>& token) const
		{
			return (token->GetType() == Lexer::TokenType::OperatorBinaryStar || token->GetType() == Lexer::TokenType::OperatorBinarySlash || token->GetType() == Lexer::TokenType::OperatorBinaryModulo);
		}

		/*
			UnaryOperator
				: '+'
				| '-'
				| '!'
				| '++'
				| '--'
				;
		*/
		bool Parser::IsUnaryOperator(const std::shared_ptr<Lexer::Token>& token) const
		{
			return (token->GetType() == Lexer::TokenType::OperatorBinaryPlus || token->GetType() == Lexer::TokenType::OperatorBinaryMinus || token->GetType() == Lexer::TokenType::OperatorLogicalNOT || token->GetType() == Lexer::TokenType::OperatorArithmeticIncrement || token->GetType() == Lexer::TokenType::OperatorArithmeticDecrement);
		}

		/*
			PostfixOperator
				: '++'
				| '--'
				;
		*/
		bool Parser::IsPostfixOperator(const std::shared_ptr<Lexer::Token>& token) const
		{
			return (token->GetType() == Lexer::TokenType::OperatorArithmeticIncrement || token->GetType() == Lexer::TokenType::OperatorArithmeticDecrement);
		}

		/*
			TypeQualifier
				: 'const'
				;
		*/
		bool Parser::IsTypeQualifierKeyword(const std::shared_ptr<Lexer::Token>& token) const
		{
			return (token->GetType() == Lexer::TokenType::KeywordTypeQualifierConst);
		}

		/*
			DatatypeKeyword
				: 'int'
				| 'float'
				| 'str'
				| 'bool'
				;
		*/
		bool Parser::IsDataTypeKeyword(const std::shared_ptr<Lexer::Token>& token) const
		{
			return (token->GetType() == Lexer::TokenType::KeywordDataTypeInt || token->GetType() == Lexer::TokenType::KeywordDataTypeFloat || token->GetType() == Lexer::TokenType::KeywordDataTypeStr || token->GetType() == Lexer::TokenType::KeywordDataTypeBool || token->GetType() == Lexer::TokenType::KeywordDataTypeVoid);
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

		std::shared_ptr<Lexer::Token> Parser::NextToken()
		{
			if (!HasToken())
				return {};

			std::shared_ptr<Lexer::Token> token = m_Tokens[m_CurrentTokenIndex++];
			while (token && (token->GetType() == Lexer::TokenType::Newline || token->GetType() == Lexer::TokenType::Comment || (token->GetType() == Lexer::TokenType::SymbolBackslash)))
			{
				if (HasToken())
					token = m_Tokens[m_CurrentTokenIndex++];
				else
					return {};
			}

			return token;
		}

		std::shared_ptr<Lexer::Token> Parser::PeekToken()
		{
			if (!HasToken())
				return {};

			std::shared_ptr<Lexer::Token> token = m_Tokens[m_CurrentTokenIndex];
			while (token && (token->GetType() == Lexer::TokenType::Newline || token->GetType() == Lexer::TokenType::Comment || (token->GetType() == Lexer::TokenType::SymbolBackslash)))
			{
				if (HasToken())
					token = m_Tokens[++m_CurrentTokenIndex];
				else
					return {};
			}

			return token;
		}

		std::shared_ptr<Lexer::Token> Parser::EatToken(Lexer::TokenType type)
		{
			std::shared_ptr<Lexer::Token> token = m_LookAhead;
			if (!token || token->GetType() != type)
				throw Error::Exceptions::SyntaxErrorException("Unexpected " + std::string(token->GetTypeString()), token->GetSource());
			m_LookAhead = NextToken();
			return token;
		}
	}
}
