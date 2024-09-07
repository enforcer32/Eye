#include "EYETypeChecker/TypeChecker.h"

#include <EYEUtility/Logger.h>
#include <EYEError/Exceptions/BadTypeConversionException.h>
#include <EYEError/Exceptions/BadTypeCompareException.h>

namespace Eye
{
	namespace TypeChecker
	{
		std::expected<bool, Error::Error> TypeChecker::TypeCheck(const std::shared_ptr<AST::Program>& ast)
		{
			m_TypeEnvironment = std::make_shared<TypeEnvironment>();
			
			try
			{
				for (const auto& stmt : ast->GetStatementList())
					TypeCheckStatement(stmt);
			}
			catch (const Error::Exceptions::BadTypeConversionException& ex)
			{
				return std::unexpected(Error::Error(Error::ErrorType::TypeCheckerBadTypeConversion, ex.what()));
			}
			catch (const Error::Exceptions::BadTypeCompareException& ex)
			{
				return std::unexpected(Error::Error(Error::ErrorType::TypeCheckerBadTypeCompare, ex.what()));
			}
			catch (...)
			{
				EYE_LOG_CRITICAL("EYETypeChecker->TypeCheck Unknown Exception!");
			}

			return true;
		}

		void TypeChecker::TypeCheckStatement(const std::shared_ptr<AST::Statement>& stmt)
		{
			if (!stmt)
				return;

			switch (stmt->GetType())
			{
			case AST::StatementType::ExpressionStatement:
				TypeCheckExpressionStatement(std::static_pointer_cast<AST::ExpressionStatement>(stmt));
				break;
			case AST::StatementType::BlockStatement:
				TypeCheckBlockStatement(std::static_pointer_cast<AST::BlockStatement>(stmt));
				break;
			case AST::StatementType::VariableStatement:
				TypeCheckVariableStatement(std::static_pointer_cast<AST::VariableStatement>(stmt));
				break;
			case AST::StatementType::ControlStatement:
				TypeCheckControlStatement(std::static_pointer_cast<AST::ControlStatement>(stmt));
				break;
			case AST::StatementType::IterationStatement:
				TypeCheckIterationStatement(std::static_pointer_cast<AST::IterationStatement>(stmt));
				break;
			default:
				EYE_LOG_CRITICAL("EYETypeChecker Unknown Statement Type!");
				break;
			}
		}

		void TypeChecker::TypeCheckExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt)
		{
			TypeCheckExpression(exprStmt->GetExpression());
		}

		void TypeChecker::TypeCheckBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt)
		{
			BeginBlockScope();
			for (const auto& stmt : blockStmt->GetStatementList())
				TypeCheckStatement(stmt);
			EndBlockScope();
		}

		Type TypeChecker(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
		{
			if (leftType == Type::Boolean || rightType == Type::Boolean)
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(leftType), binaryExpr->GetRight()->GetSource());

			if ((leftType == Type::String && rightType != Type::String) || (leftType != Type::String && rightType == Type::String))
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(leftType), binaryExpr->GetRight()->GetSource());

			if (leftType == Type::Float || rightType == Type::Float)
				return Type::Float;

			if (leftType == Type::Integer && rightType == Type::Integer)
				return Type::Integer;
		}

		void TypeChecker::TypeCheckVariableStatement(const std::shared_ptr<AST::VariableStatement>& varStmt)
		{
			Type variableType = LexerToTypeCheckerType(varStmt->GetDataType()->GetType());
			
			for (const auto& var : varStmt->GetVariableDeclarationList())
			{
				if (var->GetInitializer())
				{
					Type initializerType = TypeCheckExpression(var->GetInitializer());
					if (variableType == Type::String && initializerType != Type::String)
						throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(initializerType) + " to " + TypeToString(variableType), var->GetInitializer()->GetSource());
					else if (variableType == Type::Float && (initializerType != Type::Float && initializerType != Type::Integer))
						throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(initializerType) + " to " + TypeToString(variableType), var->GetInitializer()->GetSource());
					else if (variableType == Type::Integer && initializerType != Type::Integer)
						throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(initializerType) + " to " + TypeToString(variableType), var->GetInitializer()->GetSource());
					else if (variableType == Type::Boolean && initializerType != Type::Boolean)
						throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(initializerType) + " to " + TypeToString(variableType), var->GetInitializer()->GetSource());
				}
				m_TypeEnvironment->DefineVariable(var->GetIdentifier()->GetValue(), variableType);
			}
		}

		void TypeChecker::TypeCheckControlStatement(const std::shared_ptr<AST::ControlStatement>& ctrlStmt)
		{
			Type conditionType = TypeCheckExpression(ctrlStmt->GetCondition());
			if(conditionType != Type::Boolean)
				EYE_LOG_CRITICAL("EYETypeChecker ControlStatement->Expected {} Type for Condition (\"if()\") but got {} Type Instead!", TypeToString(Type::Boolean), TypeToString(conditionType));
			TypeCheckStatement(ctrlStmt->GetConsequent());
			TypeCheckStatement(ctrlStmt->GetAlternate());
		}

		void TypeChecker::TypeCheckIterationStatement(const std::shared_ptr<AST::IterationStatement>& iterStmt)
		{
			if (iterStmt->GetIterationType() == AST::IterationStatementType::WhileStatement)
				return TypeCheckWhileStatement(std::static_pointer_cast<AST::WhileStatement>(iterStmt));
		}

		void TypeChecker::TypeCheckWhileStatement(const std::shared_ptr<AST::WhileStatement>& whileStmt)
		{
			Type conditionType = TypeCheckExpression(whileStmt->GetCondition());
			if (conditionType != Type::Boolean)
				EYE_LOG_CRITICAL("EYETypeChecker WhileStatement->Expected {} Type for Condition (\"while()\") but got {} Type Instead!", TypeToString(Type::Boolean), TypeToString(conditionType));
			TypeCheckStatement(whileStmt->GetBody());
		}

		Type TypeChecker::TypeCheckExpression(const std::shared_ptr<AST::Expression>& expr)
		{
			/*if (!expr)
				EYE_LOG_CRITICAL("EYETypeChecker Unknown Expression Type!");*/

			switch (expr->GetType())	
			{
			case AST::ExpressionType::LiteralExpression:
				return TypeCheckLiteralExpression(std::static_pointer_cast<AST::LiteralExpression>(expr));
			case AST::ExpressionType::BinaryExpression:
				return TypeCheckBinaryExpression(std::static_pointer_cast<AST::BinaryExpression>(expr));
			default:
				EYE_LOG_CRITICAL("EYETypeChecker Unknown Expression Type!");
				break;
			}
		}

		Type TypeChecker::TypeCheckLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr)
		{
			switch (literalExpr->GetLiteralType())
			{
			case AST::LiteralType::Integer:
				return Type::Integer;
			case AST::LiteralType::Float:
				return Type::Float;
			case AST::LiteralType::String:
				return Type::String;
			case AST::LiteralType::Boolean:
				return Type::Boolean;
			default:
				EYE_LOG_CRITICAL("EYETypeChecker Unknown Type!");
				break;
			}
		}

		Type TypeChecker::TypeCheckBinaryExpression(const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
		{
			Type leftType = TypeCheckExpression(binaryExpr->GetLeft());
			Type rightType = TypeCheckExpression(binaryExpr->GetRight());
			
			switch (binaryExpr->GetOperator()->GetType())
			{
			case Lexer::TokenType::OperatorBinaryPlus:
				return TypeCheckBinaryExpressionArithmeticPlus(leftType, rightType, binaryExpr);
			case Lexer::TokenType::OperatorRelationalEquals:
			case Lexer::TokenType::OperatorRelationalNotEquals:
			case Lexer::TokenType::OperatorRelationalSmaller:
			case Lexer::TokenType::OperatorRelationalGreater:
			case Lexer::TokenType::OperatorRelationalSmallerEquals:
			case Lexer::TokenType::OperatorRelationalGreaterEquals:
				return TypeCheckBinaryExpressionRelational(leftType, rightType, binaryExpr);
			default:
				break;
			}
		}

		Type TypeChecker::TypeCheckBinaryExpressionArithmeticPlus(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
		{
			if (leftType == Type::Boolean || rightType == Type::Boolean)
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(leftType), binaryExpr->GetRight()->GetSource());

			if ((leftType == Type::String && rightType != Type::String) || (leftType != Type::String && rightType == Type::String))
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(leftType), binaryExpr->GetRight()->GetSource());

			if (leftType == Type::String && rightType == Type::String)
				return Type::String;

			if (leftType == Type::Float || rightType == Type::Float)
				return Type::Float;

			if (leftType == Type::Integer && rightType == Type::Integer)
				return Type::Integer;
		}

		Type TypeChecker::TypeCheckBinaryExpressionRelational(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
		{
			if ((leftType == Type::String && rightType != Type::String) || (leftType != Type::String && rightType == Type::String))
				throw Error::Exceptions::BadTypeCompareException("Incomparable Types: " + TypeToString(leftType) + " and " + TypeToString(rightType), binaryExpr->GetOperator()->GetSource());

			if (binaryExpr->GetOperator()->GetType() == Lexer::TokenType::OperatorRelationalEquals || binaryExpr->GetOperator()->GetType() == Lexer::TokenType::OperatorRelationalNotEquals)
			{
				if ((leftType == Type::Boolean && rightType != Type::Boolean) || (leftType != Type::Boolean && rightType == Type::Boolean))
					throw Error::Exceptions::BadTypeCompareException("Incomparable Types: " + TypeToString(leftType) + " and " + TypeToString(rightType), binaryExpr->GetOperator()->GetSource());
			}
			else
			{
				if(leftType == Type::Boolean || rightType == Type::Boolean)
					throw Error::Exceptions::BadTypeCompareException("Incomparable Types: " + TypeToString(leftType) + " and " + TypeToString(rightType), binaryExpr->GetOperator()->GetSource());
			}

			return Type::Boolean;
		}

		Type TypeChecker::LexerToTypeCheckerType(Lexer::TokenType type)
		{
			if (type == Lexer::TokenType::KeywordDataTypeInt)
				return Type::Integer;
			else if (type == Lexer::TokenType::KeywordDataTypeFloat)
				return Type::Float;
			else if (type == Lexer::TokenType::KeywordDataTypeStr)
				return Type::String;
			else if (type == Lexer::TokenType::KeywordDataTypeBool)
				return Type::Boolean;
			EYE_LOG_CRITICAL("EYETypeChecker LexerToTypeCheckerType Invalid Type!");
		}

		void TypeChecker::BeginBlockScope()
		{
			m_TypeEnvironment = std::make_shared<TypeEnvironment>(m_TypeEnvironment);
		}

		void TypeChecker::EndBlockScope()
		{
			m_TypeEnvironment = m_TypeEnvironment->GetParent();
		}
	}
}
