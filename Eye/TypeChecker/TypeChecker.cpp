#include "Eye/TypeChecker/TypeChecker.h"
#include "Eye/Utility/Logger.h"
#include "Eye/Error/Exceptions/BadTypeConversionException.h"
#include "Eye/Error/Exceptions/BadTypeCompareException.h"
#include "Eye/Error/Exceptions/BadOperandTypeException.h"

namespace Eye
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
		catch (const Error::Exceptions::EyeException& ex)
		{
			return std::unexpected(ex.GetError());
		}
		catch (...)
		{
			EYE_LOG_CRITICAL("EYETypeChecker->TypeCheck Unsupported Exception!");
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
			EYE_LOG_CRITICAL("EYETypeChecker Unsupported Statement Type!");
			break;
		}
	}

	void TypeChecker::TypeCheckExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt)
	{
		TypeCheckExpression(exprStmt->GetExpression());
	}

	void TypeChecker::TypeCheckBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt, bool createScope)
	{
		if (createScope)
			BeginBlockScope();
		for (const auto& stmt : blockStmt->GetStatementList())
			TypeCheckStatement(stmt);
		if (createScope)
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
					throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(initializerType) + " to " + TypeToString(variableType), Error::ErrorType::TypeCheckerBadTypeConversion, var->GetInitializer()->GetSource());
				else if (variableType == Type::Float && (initializerType != Type::Float && initializerType != Type::Integer))
					throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(initializerType) + " to " + TypeToString(variableType), Error::ErrorType::TypeCheckerBadTypeConversion, var->GetInitializer()->GetSource());
				else if (variableType == Type::Integer && initializerType != Type::Integer)
					throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(initializerType) + " to " + TypeToString(variableType), Error::ErrorType::TypeCheckerBadTypeConversion, var->GetInitializer()->GetSource());
				else if (variableType == Type::Boolean && initializerType != Type::Boolean)
					throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(initializerType) + " to " + TypeToString(variableType), Error::ErrorType::TypeCheckerBadTypeConversion, var->GetInitializer()->GetSource());
			}
			m_TypeEnvironment->Define(var->GetIdentifier()->GetValue(), variableType);
		}
	}

	void TypeChecker::TypeCheckControlStatement(const std::shared_ptr<AST::ControlStatement>& ctrlStmt)
	{
		Type conditionType = TypeCheckExpression(ctrlStmt->GetCondition());
		if (conditionType != Type::Boolean && conditionType != Type::Integer)
			throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(conditionType) + " to " + TypeToString(Type::Boolean), Error::ErrorType::TypeCheckerBadTypeConversion, ctrlStmt->GetSource());
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
			throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(conditionType) + " to " + TypeToString(Type::Boolean), Error::ErrorType::TypeCheckerBadTypeConversion, whileStmt->GetSource());
		TypeCheckStatement(whileStmt->GetBody());
	}

	void TypeChecker::TypeCheckDoWhileStatement(const std::shared_ptr<AST::DoWhileStatement>& doStmt)
	{
		Type conditionType = TypeCheckExpression(doStmt->GetCondition());
		if (conditionType != Type::Boolean && conditionType != Type::Integer)
			throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(conditionType) + " to " + TypeToString(Type::Boolean), Error::ErrorType::TypeCheckerBadTypeConversion, doStmt->GetSource());
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
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(conditionType) + " to " + TypeToString(Type::Boolean), Error::ErrorType::TypeCheckerBadTypeConversion, forStmt->GetSource());
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
						throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(returnType) + " to " + TypeToString(funcType.Return), Error::ErrorType::TypeCheckerBadTypeConversion, stmt->GetSource());
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
			EYE_LOG_CRITICAL("EYETypeChecker TypeCheckExpression Unsupported Expression Type!");
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
			EYE_LOG_CRITICAL("EYETypeChecker TypeCheckLiteralExpression Unsupported Type!");
			break;
		}
	}

	Type TypeChecker::TypeCheckIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr)
	{
		return m_TypeEnvironment->Get(identifierExpr->GetValue());
	}

	Type TypeChecker::TypeCheckAssignmentExpression(const std::shared_ptr<AST::AssignmentExpression>& assignExpr)
	{
		Type lhsType = TypeCheckExpression(assignExpr->GetLHSExpression());
		Type rightType = TypeCheckExpression(assignExpr->GetExpression());

		switch (assignExpr->GetOperator()->GetType())
		{
		case TokenType::OperatorAssignment:
			return TypeCheckAssignmentExpressionAssignment(lhsType, rightType, assignExpr);
		case TokenType::OperatorAssignmentPlus:
		case TokenType::OperatorAssignmentMinus:
		case TokenType::OperatorAssignmentStar:
		case TokenType::OperatorAssignmentSlash:
		case TokenType::OperatorAssignmentModulo:
			return TypeCheckAssignmentExpressionAssignmentArithmetic(lhsType, rightType, assignExpr);
		case TokenType::OperatorAssignmentBitwiseAND:
		case TokenType::OperatorAssignmentBitwiseOR:
		case TokenType::OperatorAssignmentBitwiseXOR:
		case TokenType::OperatorAssignmentBitwiseLeftShift:
		case TokenType::OperatorAssignmentBitwiseRightShift:
			return TypeCheckAssignmentExpressionAssignmentBitwsie(lhsType, rightType, assignExpr);
		default:
			break;
		}

		EYE_LOG_CRITICAL("EYETypeChecker TypeCheckAssignmentExpression Unsupported Operator {}", assignExpr->GetOperator()->GetValueString());
	}

	Type TypeChecker::TypeCheckAssignmentExpressionAssignment(Type lhsType, Type rightType, const std::shared_ptr<AST::AssignmentExpression>& assignExpr)
	{
		if (lhsType == Type::String && rightType != Type::String)
			throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(lhsType), Error::ErrorType::TypeCheckerBadTypeConversion, assignExpr->GetSource());
		else if (lhsType == Type::Float && (rightType != Type::Float && rightType != Type::Integer))
			throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(lhsType), Error::ErrorType::TypeCheckerBadTypeConversion, assignExpr->GetSource());
		else if (lhsType == Type::Integer && rightType != Type::Integer)
			throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(lhsType), Error::ErrorType::TypeCheckerBadTypeConversion, assignExpr->GetSource());
		else if (lhsType == Type::Boolean && rightType != Type::Boolean)
			throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(lhsType), Error::ErrorType::TypeCheckerBadTypeConversion, assignExpr->GetSource());
		return lhsType;
	}

	Type TypeChecker::TypeCheckAssignmentExpressionAssignmentArithmetic(Type lhsType, Type rightType, const std::shared_ptr<AST::AssignmentExpression>& assignExpr)
	{
		if (lhsType == Type::Boolean || rightType == Type::Boolean)
			throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + (lhsType == Type::Boolean ? TypeToString(lhsType) : TypeToString(rightType)) + " for Assignment Operator '" + assignExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, assignExpr->GetSource());

		if (assignExpr->GetOperator()->GetType() != TokenType::OperatorAssignmentPlus)
			if (lhsType == Type::String || rightType == Type::String)
				throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + (lhsType == Type::String ? TypeToString(lhsType) : TypeToString(rightType)) + " for Assignment Operator '" + assignExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, assignExpr->GetSource());

		if (lhsType == Type::String && rightType != Type::String)
			throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(lhsType), Error::ErrorType::TypeCheckerBadTypeConversion, assignExpr->GetSource());

		if (lhsType == Type::Float && (rightType != Type::Float && rightType != Type::Integer))
			throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(lhsType), Error::ErrorType::TypeCheckerBadTypeConversion, assignExpr->GetSource());

		if (lhsType == Type::Integer && rightType != Type::Integer)
			throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(lhsType), Error::ErrorType::TypeCheckerBadTypeConversion, assignExpr->GetSource());

		return lhsType;
	}

	Type TypeChecker::TypeCheckAssignmentExpressionAssignmentBitwsie(Type lhsType, Type rightType, const std::shared_ptr<AST::AssignmentExpression>& assignExpr)
	{
		if (lhsType != Type::Integer || rightType != Type::Integer)
			throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + (lhsType != Type::Integer ? TypeToString(lhsType) : TypeToString(rightType)) + " for Assignment Operator '" + assignExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, assignExpr->GetSource());
		return lhsType;
	}

	Type TypeChecker::TypeCheckBinaryExpression(const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
	{
		Type leftType = TypeCheckExpression(binaryExpr->GetLeft());
		Type rightType = TypeCheckExpression(binaryExpr->GetRight());

		switch (binaryExpr->GetOperator()->GetType())
		{
		case TokenType::OperatorBinaryPlus:
		case TokenType::OperatorBinaryMinus:
		case TokenType::OperatorBinaryStar:
		case TokenType::OperatorBinarySlash:
		case TokenType::OperatorBinaryModulo:
			return TypeCheckBinaryExpressionArithmetic(leftType, rightType, binaryExpr);
		case TokenType::OperatorRelationalEquals:
		case TokenType::OperatorRelationalNotEquals:
		case TokenType::OperatorRelationalSmaller:
		case TokenType::OperatorRelationalGreater:
		case TokenType::OperatorRelationalSmallerEquals:
		case TokenType::OperatorRelationalGreaterEquals:
			return TypeCheckBinaryExpressionRelational(leftType, rightType, binaryExpr);
		case TokenType::OperatorLogicalOR:
		case TokenType::OperatorLogicalAND:
			return TypeCheckBinaryExpressionLogical(leftType, rightType, binaryExpr);
		case TokenType::OperatorBitwiseBinaryAND:
		case TokenType::OperatorBitwiseBinaryOR:
		case TokenType::OperatorBitwiseBinaryXOR:
		case TokenType::OperatorBitwiseLeftShift:
		case TokenType::OperatorBitwiseRightShift:
			return TypeCheckBinaryExpressionBitwise(leftType, rightType, binaryExpr);
		default:
			break;
		}

		EYE_LOG_CRITICAL("EYETypeChecker TypeCheckBinaryExpression Unsupported Operator {}", binaryExpr->GetOperator()->GetValueString());
	}

	Type TypeChecker::TypeCheckBinaryExpressionArithmetic(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
	{
		if (leftType == Type::Boolean || rightType == Type::Boolean)
			throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + (leftType == Type::Boolean ? TypeToString(leftType) : TypeToString(rightType)) + " for Binary Operator '" + binaryExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, binaryExpr->GetSource());

		if (binaryExpr->GetOperator()->GetType() == TokenType::OperatorBinaryPlus)
		{
			if (leftType == Type::String && rightType == Type::String)
				return Type::String;

			if ((leftType == Type::String && rightType != Type::String) || (leftType != Type::String && rightType == Type::String))
				throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(rightType) + " to " + TypeToString(leftType), Error::ErrorType::TypeCheckerBadTypeConversion, binaryExpr->GetRight()->GetSource());
		}
		else
		{
			if (leftType == Type::String || rightType == Type::String)
				throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + (leftType == Type::String ? TypeToString(leftType) : TypeToString(rightType)) + " for Binary Operator '" + binaryExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, binaryExpr->GetSource());
		}

		if (leftType == Type::Float || rightType == Type::Float)
			return Type::Float;

		if (leftType == Type::Integer && rightType == Type::Integer)
			return Type::Integer;

		EYE_LOG_CRITICAL("EYETypeChecker TypeCheckBinaryExpressionArithmetic Invalid Types {}, {}", TypeToString(leftType), TypeToString(rightType));
	}

	Type TypeChecker::TypeCheckBinaryExpressionRelational(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
	{
		if ((leftType == Type::String && rightType != Type::String) || (leftType != Type::String && rightType == Type::String))
			throw Error::Exceptions::BadTypeCompareException("Incomparable Types: " + TypeToString(leftType) + " and " + TypeToString(rightType), Error::ErrorType::TypeCheckerBadTypeCompare, binaryExpr->GetOperator()->GetSource());

		if (binaryExpr->GetOperator()->GetType() == TokenType::OperatorRelationalEquals || binaryExpr->GetOperator()->GetType() == TokenType::OperatorRelationalNotEquals)
		{
			if ((leftType == Type::Boolean && rightType != Type::Boolean) || (leftType != Type::Boolean && rightType == Type::Boolean))
				throw Error::Exceptions::BadTypeCompareException("Incomparable Types: " + TypeToString(leftType) + " and " + TypeToString(rightType), Error::ErrorType::TypeCheckerBadTypeCompare, binaryExpr->GetOperator()->GetSource());
		}
		else
		{
			if (leftType == Type::Boolean || rightType == Type::Boolean)
				throw Error::Exceptions::BadTypeCompareException("Incomparable Types: " + TypeToString(leftType) + " and " + TypeToString(rightType), Error::ErrorType::TypeCheckerBadTypeCompare, binaryExpr->GetOperator()->GetSource());
		}

		return Type::Boolean;
	}

	Type TypeChecker::TypeCheckBinaryExpressionLogical(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
	{
		if (leftType != Type::Boolean && leftType != Type::Integer)
			throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(leftType) + " for Binary Operator '" + binaryExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, binaryExpr->GetSource());
		else if (rightType != Type::Boolean && rightType != Type::Integer)
			throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(rightType) + " for Binary Operator '" + binaryExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, binaryExpr->GetSource());
		return Type::Boolean;
	}

	Type TypeChecker::TypeCheckBinaryExpressionBitwise(Type leftType, Type rightType, const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
	{
		if (leftType != Type::Integer || rightType != Type::Integer)
			throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + (leftType != Type::Integer ? TypeToString(leftType) : TypeToString(rightType)) + " for Binary Operator '" + binaryExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, binaryExpr->GetSource());
		return Type::Integer;
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
					throw Error::Exceptions::BadTypeConversionException("Invalid Conversion from " + TypeToString(argType) + " to " + TypeToString(paramType), Error::ErrorType::TypeCheckerBadTypeConversion, callExpr->GetSource());
			}

			return funcType.Return;
		}

		EYE_LOG_CRITICAL("EYETypeChecker TypeCheckCallExpression Unsupported Type!");
	}

	Type TypeChecker::TypeCheckUnaryExpression(const std::shared_ptr<AST::UnaryExpression>& unaryExpr)
	{
		Type exprType = TypeCheckExpression(unaryExpr->GetExpression());
		if (unaryExpr->GetOperator()->GetType() == TokenType::OperatorBinaryPlus || unaryExpr->GetOperator()->GetType() == TokenType::OperatorBinaryMinus)
		{
			if (exprType != Type::Integer && exprType != Type::Float)
				throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(exprType) + " for Unary Operator '" + unaryExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, unaryExpr->GetSource());
		}
		else if (unaryExpr->GetOperator()->GetType() == TokenType::OperatorLogicalNOT)
		{
			if (exprType != Type::Boolean && exprType != Type::Integer)
				throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(exprType) + " for Unary Operator '" + unaryExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, unaryExpr->GetSource());
		}
		else if (unaryExpr->GetOperator()->GetType() == TokenType::OperatorBitwiseNOT)
		{
			if (exprType != Type::Integer)
				throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(exprType) + " for Unary Operator '" + unaryExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, unaryExpr->GetSource());
		}
		else
		{
			EYE_LOG_CRITICAL("EYETypeChecker TypeCheckUnaryExpression Unsupported Operator {}", unaryExpr->GetOperator()->GetValueString());
		}

		return exprType;
	}

	Type TypeChecker::TypeCheckPostfixExpression(const std::shared_ptr<AST::PostfixExpression>& postfixExpr)
	{
		if (postfixExpr->GetOperator()->GetType() == TokenType::OperatorArithmeticIncrement || postfixExpr->GetOperator()->GetType() == TokenType::OperatorArithmeticDecrement)
		{
			Type exprType = TypeCheckExpression(postfixExpr->GetExpression());
			if (exprType != Type::Integer && exprType != Type::Float)
				throw Error::Exceptions::BadOperandTypeException("Bad Operand Type " + TypeToString(exprType) + " for Postfix Operator '" + postfixExpr->GetOperator()->GetValueString() + "'", Error::ErrorType::TypeCheckerBadOperandType, postfixExpr->GetSource());
			return exprType;
		}

		EYE_LOG_CRITICAL("EYETypeChecker TypeCheckPostfixExpression Unsupported Operator {}", postfixExpr->GetOperator()->GetValueString());
	}

	Type TypeChecker::LexerToTypeCheckerType(TokenType type)
	{
		if (type == TokenType::KeywordDataTypeInt)
			return Type::Integer;
		else if (type == TokenType::KeywordDataTypeFloat)
			return Type::Float;
		else if (type == TokenType::KeywordDataTypeStr)
			return Type::String;
		else if (type == TokenType::KeywordDataTypeBool)
			return Type::Boolean;
		else if (type == TokenType::KeywordDataTypeVoid)
			return Type::Void;
		else if (type == TokenType::KeywordFunction)
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
