#include "EYETypeChecker/TypeChecker.h"

#include <EYEUtility/Logger.h>
#include <EYEError/Exceptions/BadTypeConversionException.h>
#include <EYEError/Exceptions/BadTypeCompareException.h>
#include <EYEError/Exceptions/BadOperandTypeException.h>

namespace Eye
{
	namespace TypeChecker
	{
		std::expected<bool, Error::Error> TypeChecker::TypeCheck(const std::shared_ptr<AST::Program>& ast)
		{
			m_TypeEnvironment = std::make_shared<Environment<Type>>();
			m_FunctionEnvironment = std::make_shared<Environment<FunctionType>>();
			
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
			catch (const Error::Exceptions::BadOperandTypeException& ex)
			{
				return std::unexpected(Error::Error(Error::ErrorType::TypeCheckerBadOperandType, ex.what()));
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
			case AST::StatementType::FunctionStatement:
				TypeCheckFunctionStatement(std::static_pointer_cast<AST::FunctionStatement>(stmt));
				break;
			case AST::StatementType::ReturnStatement:
				TypeCheckReturnStatement(std::static_pointer_cast<AST::ReturnStatement>(stmt));
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

		void TypeChecker::TypeCheckBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt, bool createScope)
		{
			if(createScope)
				BeginBlockScope();
			for (const auto& stmt : blockStmt->GetStatementList())
				TypeCheckStatement(stmt);
			if(createScope)
				EndBlockScope();
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
				m_TypeEnvironment->Define(var->GetIdentifier()->GetValue(), variableType);
			}
		}

		void TypeChecker::TypeCheckControlStatement(const std::shared_ptr<AST::ControlStatement>& ctrlStmt)
		{
			Type conditionType = TypeCheckExpression(ctrlStmt->GetCondition());
			if (conditionType != Type::Boolean && conditionType != Type::Integer)
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(conditionType) + " to " + TypeToString(Type::Boolean), ctrlStmt->GetSource());
			TypeCheckStatement(ctrlStmt->GetConsequent());
			TypeCheckStatement(ctrlStmt->GetAlternate());
		}

		void TypeChecker::TypeCheckIterationStatement(const std::shared_ptr<AST::IterationStatement>& iterStmt)
		{
			switch (iterStmt->GetIterationType())
			{
			case AST::IterationStatementType::WhileStatement:
				return TypeCheckWhileStatement(std::static_pointer_cast<AST::WhileStatement>(iterStmt));
			case AST::IterationStatementType::DoWhileStatement:
				return TypeCheckDoWhileStatement(std::static_pointer_cast<AST::DoWhileStatement>(iterStmt));
			case AST::IterationStatementType::ForStatement:
				return TypeCheckForStatement(std::static_pointer_cast<AST::ForStatement>(iterStmt));
			default:
				break;
			}
		}

		void TypeChecker::TypeCheckWhileStatement(const std::shared_ptr<AST::WhileStatement>& whileStmt)
		{
			Type conditionType = TypeCheckExpression(whileStmt->GetCondition());
			if (conditionType != Type::Boolean && conditionType != Type::Integer)
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(conditionType) + " to " + TypeToString(Type::Boolean), whileStmt->GetSource());
			TypeCheckStatement(whileStmt->GetBody());
		}

		void TypeChecker::TypeCheckDoWhileStatement(const std::shared_ptr<AST::DoWhileStatement>& doStmt)
		{
			Type conditionType = TypeCheckExpression(doStmt->GetCondition());
			if (conditionType != Type::Boolean && conditionType != Type::Integer)
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(conditionType) + " to " + TypeToString(Type::Boolean), doStmt->GetSource());
			TypeCheckStatement(doStmt->GetBody());
		}

		void TypeChecker::TypeCheckForStatement(const std::shared_ptr<AST::ForStatement>& forStmt)
		{
			switch (forStmt->GetInitializerType())
			{
			case AST::ForInitializerType::Expression:
				TypeCheckExpression(forStmt->GetInitializer<AST::Expression>());
				break;
			case AST::ForInitializerType::VariableStatement:
				TypeCheckVariableStatement(forStmt->GetInitializer<AST::VariableStatement>());
				break;
			default:
				break;
			}

			if (forStmt->GetCondition())
			{
				Type conditionType = TypeCheckExpression(forStmt->GetCondition());
				if (conditionType != Type::Boolean && conditionType != Type::Integer)
					throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(conditionType) + " to " + TypeToString(Type::Boolean), forStmt->GetSource());
			}

			if (forStmt->GetUpdate())
				TypeCheckExpression(forStmt->GetUpdate());

			TypeCheckStatement(forStmt->GetBody());
		}

		void TypeChecker::TypeCheckFunctionStatement(const std::shared_ptr<AST::FunctionStatement>& functionStmt)
		{
			FunctionType funcType;
			funcType.Return = LexerToTypeCheckerType(functionStmt->GetReturnType()->GetType());
			for (const auto& param : functionStmt->GetParameters())
				funcType.Parameters.push_back(LexerToTypeCheckerType(param->GetDataType()->GetType()));

			m_FunctionEnvironment->Define(functionStmt->GetIdentifier()->GetValue(), funcType);
			m_TypeEnvironment->Define(functionStmt->GetIdentifier()->GetValue(), Type::Function);

			BeginBlockScope();

			for (const auto& param : functionStmt->GetParameters())
				m_TypeEnvironment->Define(param->GetIdentifier()->GetValue(), LexerToTypeCheckerType(param->GetDataType()->GetType()));

			TypeCheckBlockStatement(functionStmt->GetBody(), false);

			if (funcType.Return != Type::Void)
			{
				for (const auto& stmt : functionStmt->GetBody()->GetStatementList())
				{
					if (stmt->GetType() == AST::StatementType::ReturnStatement)
					{
						Type returnType = TypeCheckExpression(std::static_pointer_cast<AST::ReturnStatement>(stmt)->GetExpression());
						if (funcType.Return == Type::Float && returnType == Type::Integer)
							continue;
						else if (funcType.Return != returnType)
							throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(returnType) + " to " + TypeToString(funcType.Return), stmt->GetSource());
					}
				}
			}

			EndBlockScope();
		}

		void TypeChecker::TypeCheckReturnStatement(const std::shared_ptr<AST::ReturnStatement>& returnStmt)
		{
		}

		Type TypeChecker::TypeCheckExpression(const std::shared_ptr<AST::Expression>& expr)
		{
			/*if (!expr)
				EYE_LOG_CRITICAL("EYETypeChecker Unknown Expression Type!");*/

			switch (expr->GetType())	
			{
			case AST::ExpressionType::LiteralExpression:
				return TypeCheckLiteralExpression(std::static_pointer_cast<AST::LiteralExpression>(expr));
			case AST::ExpressionType::IdentifierExpression:
				return TypeCheckIdentifierExpression(std::static_pointer_cast<AST::IdentifierExpression>(expr));
			case AST::ExpressionType::AssignmentExpression:
				return TypeCheckAssignmentExpression(std::static_pointer_cast<AST::AssignmentExpression>(expr));
			case AST::ExpressionType::BinaryExpression:
				return TypeCheckBinaryExpression(std::static_pointer_cast<AST::BinaryExpression>(expr));
			case AST::ExpressionType::CallExpression:
				return TypeCheckCallExpression(std::static_pointer_cast<AST::CallExpression>(expr));
			case AST::ExpressionType::UnaryExpression:
				return TypeCheckUnaryExpression(std::static_pointer_cast<AST::UnaryExpression>(expr));
			case AST::ExpressionType::PostfixExpression:
				return TypeCheckPostfixExpression(std::static_pointer_cast<AST::PostfixExpression>(expr));
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

		Type TypeChecker::TypeCheckIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr)
		{
			return m_TypeEnvironment->Get(identifierExpr->GetValue());
		}

		Type TypeChecker::TypeCheckAssignmentExpression(const std::shared_ptr<AST::AssignmentExpression>& assignExpr)
		{
			Type leftType = TypeCheckExpression(assignExpr->GetLHSExpression());
			Type rightType = TypeCheckExpression(assignExpr->GetExpression());

			if (leftType == Type::String && rightType != Type::String)
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(leftType), assignExpr->GetSource());
			else if (leftType == Type::Float && (rightType != Type::Float && rightType != Type::Integer))
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(leftType), assignExpr->GetSource());
			else if (leftType == Type::Integer && rightType != Type::Integer)
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(leftType), assignExpr->GetSource());
			else if (leftType == Type::Boolean && rightType != Type::Boolean)
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(leftType), assignExpr->GetSource());

			return leftType;
		}

		Type TypeChecker::TypeCheckCallExpression(const std::shared_ptr<AST::CallExpression>& callExpr)
		{
			Type calleeType = TypeCheckExpression(callExpr->GetCallee());
			if (calleeType == Type::Function)
			{
				const FunctionType& funcType = m_FunctionEnvironment->Get(std::static_pointer_cast<AST::IdentifierExpression>(callExpr->GetCallee())->GetValue());

				for (size_t i = 0; i < funcType.Parameters.size(); i++)
				{
					Type paramType = funcType.Parameters[i];
					Type argType = TypeCheckExpression(callExpr->GetArguments()[i]);
					if (argType != paramType)
						throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(argType) + " to " + TypeToString(paramType), callExpr->GetSource());
				}

				return funcType.Return;
			}

			EYE_LOG_CRITICAL("EYETypeChecker TypeCheckCallExpression Invalid Type!");
		}

		Type TypeChecker::TypeCheckUnaryExpression(const std::shared_ptr<AST::UnaryExpression>& unaryExpr)
		{
			Type exprType = TypeCheckExpression(unaryExpr->GetExpression());
			if (unaryExpr->GetOperator()->GetType() == Lexer::TokenType::OperatorBinaryPlus || unaryExpr->GetOperator()->GetType() == Lexer::TokenType::OperatorBinaryMinus)
			{
				if (exprType != Type::Integer && exprType != Type::Float)
					throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(exprType) + " for Unary Operator '" + unaryExpr->GetOperator()->GetValueString() + "'", unaryExpr->GetSource());
			}
			else if (unaryExpr->GetOperator()->GetType() == Lexer::TokenType::OperatorLogicalNOT)
			{
				if (exprType != Type::Boolean && exprType != Type::Integer)
					throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(exprType) + " for Unary Operator '" + unaryExpr->GetOperator()->GetValueString() + "'", unaryExpr->GetSource());
			}

			return exprType;
		}

		Type TypeChecker::TypeCheckPostfixExpression(const std::shared_ptr<AST::PostfixExpression>& postfixExpr)
		{
			Type exprType = TypeCheckExpression(postfixExpr->GetExpression());
			if (exprType != Type::Integer && exprType != Type::Float)
				throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(exprType) + " for Postfix Operator '" + postfixExpr->GetOperator()->GetValueString() + "'", postfixExpr->GetSource());
			return exprType;
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
			case Lexer::TokenType::OperatorLogicalOR:
			case Lexer::TokenType::OperatorLogicalAND:
				return TypeCheckBinaryExpressionLogical(leftType, rightType, binaryExpr);
			default:
				break;
			}

			EYE_LOG_CRITICAL("EYETypeChecker TypeCheckBinaryExpression Invalid Operator {}", binaryExpr->GetOperator()->GetValueString());
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

		Type TypeChecker::TypeCheckBinaryExpressionLogical(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
		{
			if (leftType != Type::Boolean && leftType != Type::Integer)
				throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(leftType) + " for Binary Operator '" + binaryExpr->GetOperator()->GetValueString() + "'", binaryExpr->GetSource());
			else if (rightType != Type::Boolean && rightType != Type::Integer)
				throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(rightType) + " for Binary Operator '" + binaryExpr->GetOperator()->GetValueString() + "'", binaryExpr->GetSource());
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
			else if (type == Lexer::TokenType::KeywordDataTypeVoid)
				return Type::Void;
			else if (type == Lexer::TokenType::KeywordFunction)
				return Type::Function;
			EYE_LOG_CRITICAL("EYETypeChecker LexerToTypeCheckerType Invalid Type!");
		}

		void TypeChecker::BeginBlockScope()
		{
			m_TypeEnvironment = std::make_shared<Environment<Type>>(m_TypeEnvironment);
			m_FunctionEnvironment = std::make_shared<Environment<FunctionType>>(m_FunctionEnvironment);
		}

		void TypeChecker::EndBlockScope()
		{
			m_FunctionEnvironment = m_FunctionEnvironment->GetParent();
			m_TypeEnvironment = m_TypeEnvironment->GetParent();
		}
	}
}
