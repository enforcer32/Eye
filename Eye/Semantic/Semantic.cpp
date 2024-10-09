#include "Eye/Semantic/Semantic.h"
#include "Eye/Utility/Logger.h"
#include "Eye/Error/Exceptions/NotDeclaredException.h"
#include "Eye/Error/Exceptions/ReDeclarationException.h"
#include "Eye/Error/Exceptions/BadDataTypeException.h"
#include "Eye/Error/Exceptions/WriteReadOnlyException.h"
#include "Eye/Error/Exceptions/ReturnException.h"
#include "Eye/Error/Exceptions/CallException.h"
#include "Eye/Error/Exceptions/ArgumentException.h"

#include <functional>

namespace Eye
{
	std::expected<bool, Error::Error> Semantic::Validate(const AST::Program* ast)
	{
		m_DeclarationEnvironment = std::make_shared<MapEnvironment<DeclarationType>>();
		m_FunctionDeclarationEnvironment = std::make_shared<MapEnvironment<FunctionDeclaration>>();
		m_VariableTypeQualifierEnvironment = std::make_shared<MapEnvironment<VariableTypeQualifier>>();

		try
		{
			for (const auto& stmt : ast->GetStatementList())
				ValidateStatement(stmt.get());
		}
		catch (const Error::Exceptions::EyeException& ex)
		{
			return std::unexpected(ex.GetError());
		}
		catch (...)
		{
			EYE_LOG_CRITICAL("EYESemantic->Validate Unsupported Exception!");
		}

		return true;
	}

	void Semantic::ValidateStatement(const AST::Statement* stmt)
	{
		switch (stmt->GetType())
		{
		case AST::StatementType::ExpressionStatement:
			ValidateExpressionStatement(static_cast<const AST::ExpressionStatement*>(stmt));
			break;
		case AST::StatementType::BlockStatement:
			ValidateBlockStatement(static_cast<const AST::BlockStatement*>(stmt));
			break;
		case AST::StatementType::VariableStatement:
			ValidateVariableStatement(static_cast<const AST::VariableStatement*>(stmt));
			break;
		case AST::StatementType::FunctionStatement:
			ValidateFunctionStatement(static_cast<const AST::FunctionStatement*>(stmt));
			break;
		case AST::StatementType::ReturnStatement:
			ValidateReturnStatement(static_cast<const AST::ReturnStatement*>(stmt));
			break;
		default:
			EYE_LOG_CRITICAL("EYESemantic ValidateStatement Unsupported Statement Type!");
			break;
		}
	}

	void Semantic::ValidateExpressionStatement(const AST::ExpressionStatement* exprStmt)
	{
		ValidateExpression(exprStmt->GetExpression());
	}

	void Semantic::ValidateBlockStatement(const AST::BlockStatement* blockStmt, bool createScope)
	{
		if (createScope)
			BeginBlockScope();
		for (const auto& stmt : blockStmt->GetStatementList())
			ValidateStatement(stmt.get());
		if (createScope)
			EndBlockScope();
	}

	void Semantic::ValidateVariableStatement(const AST::VariableStatement* varStmt)
	{
		if (varStmt->GetDataType()->GetType() == TokenType::KeywordDataTypeVoid)
			throw Error::Exceptions::BadDataTypeException("Variable Declared as void", Error::ErrorType::SemanticBadDataType, varStmt->GetSource());

		VariableTypeQualifier typeQualifier = VariableTypeQualifier::None;
		if (varStmt->GetTypeQualifier() && varStmt->GetTypeQualifier()->GetType() == TokenType::KeywordTypeQualifierConst)
			typeQualifier = VariableTypeQualifier::Const;

		for (const auto& var : varStmt->GetVariableDeclarationList())
		{
			if (m_DeclarationEnvironment->Has(var->GetIdentifier()->GetValue(), false))
				throw Error::Exceptions::ReDeclarationException("ReDeclaration of '" + var->GetIdentifier()->GetValue() + "'", Error::ErrorType::SemanticReDeclaration, var->GetIdentifier()->GetSource());

			if (var->GetInitializer())
				ValidateExpression(var->GetInitializer());

			m_DeclarationEnvironment->Define(var->GetIdentifier()->GetValue(), DeclarationType::Variable);
			m_VariableTypeQualifierEnvironment->Define(var->GetIdentifier()->GetValue(), typeQualifier);
		}
	}

	void Semantic::ValidateFunctionStatement(const AST::FunctionStatement* functionStmt)
	{
		if (m_DeclarationEnvironment->Has(functionStmt->GetIdentifier()->GetValue()))
			throw Error::Exceptions::ReDeclarationException("ReDeclaration of '" + functionStmt->GetIdentifier()->GetValue() + "'", Error::ErrorType::SemanticReDeclaration, functionStmt->GetIdentifier()->GetSource());
	
		FunctionDeclaration funcDec;
		FunctionParameterType paramType;
		for (const auto& param : functionStmt->GetParameters())
		{
			if (param->GetInitializer())
			{
				ValidateExpression(param->GetInitializer());
				funcDec.DefaultParameterCount++;
				paramType = FunctionParameterType::Default;
			}
			else
			{
				funcDec.RequiredParameterCount++;
				paramType = FunctionParameterType::Required;
			}

			funcDec.Parameters.push_back(paramType);
		}

		ValidateFunctionParameters(functionStmt, funcDec);

		m_DeclarationEnvironment->Define(functionStmt->GetIdentifier()->GetValue(), DeclarationType::Function);
		m_FunctionDeclarationEnvironment->Define(functionStmt->GetIdentifier()->GetValue(), funcDec);

		BeginBlockScope();
		
		for (const auto& param : functionStmt->GetParameters())
		{
			VariableTypeQualifier typeQualifier = VariableTypeQualifier::None;
			if (param->GetTypeQualifier() && param->GetTypeQualifier()->GetType() == TokenType::KeywordTypeQualifierConst)
				typeQualifier = VariableTypeQualifier::Const;

			m_DeclarationEnvironment->Define(param->GetIdentifier()->GetValue(), DeclarationType::Variable);
			m_VariableTypeQualifierEnvironment->Define(param->GetIdentifier()->GetValue(), typeQualifier);
		}

		ValidateBlockStatement(functionStmt->GetBody(), false);
		ValidateFunctionReturnStatement(functionStmt);

		EndBlockScope();
	}

	void Semantic::ValidateFunctionReturnStatement(const AST::FunctionStatement* functionStmt)
	{
		bool functionReturns = (functionStmt->GetReturnType()->GetType() != TokenType::KeywordDataTypeVoid);
		bool foundReturn = false;
	
		std::function<void(const AST::BlockStatement* block)> validateReturn = [&](const AST::BlockStatement* block) -> void
			{
				for (const auto& stmt : block->GetStatementList())
				{
					if (stmt->GetType() == AST::StatementType::ReturnStatement)
					{
						if (!functionReturns)
							throw Error::Exceptions::ReturnException("Cannot Return From Void Function '" + functionStmt->GetIdentifier()->GetValue() + "()'", Error::ErrorType::SemanticReturnFromVoid, stmt->GetSource());

						if (foundReturn)
							throw Error::Exceptions::ReturnException("Cannot Return Multiple Times per Scope for Function '" + functionStmt->GetIdentifier()->GetValue() + "()'", Error::ErrorType::SemanticMultipleReturn, stmt->GetSource());

						foundReturn = true;
					}
					else if (stmt->GetType() == AST::StatementType::BlockStatement)
					{
						validateReturn(static_cast<const AST::BlockStatement*>(stmt.get()));
					}
				}

				if (functionReturns && !foundReturn)
					throw Error::Exceptions::ReturnException("Non-Void Functions Must Always Return '" + functionStmt->GetIdentifier()->GetValue() + "()'", Error::ErrorType::SemanticNoReturn, functionStmt->GetSource());
			};

		validateReturn(functionStmt->GetBody());
	}

	void Semantic::ValidateFunctionParameters(const AST::FunctionStatement* functionStmt, const FunctionDeclaration& functionDec)
	{
		if (functionDec.Parameters.size())
		{
			for (size_t i = functionDec.Parameters.size() - 1; i > 0; i--)
				if (functionDec.Parameters[i] == FunctionParameterType::Required && functionDec.Parameters[i - 1] == FunctionParameterType::Default)
					throw Error::Exceptions::ArgumentException("Default Argument Missing for Parameter " + std::to_string(i + 1) + " of '" + functionStmt->GetIdentifier()->GetValue() + "()'", Error::ErrorType::SemanticMissingArgument, functionStmt->GetSource());
		}
	}

	void Semantic::ValidateReturnStatement(const AST::ReturnStatement* returnStmt)
	{
		ValidateExpression(returnStmt->GetExpression());
	}

	void Semantic::ValidateExpression(const AST::Expression* expr)
	{
		switch (expr->GetType())
		{
		case AST::ExpressionType::LiteralExpression:
			ValidateLiteralExpression(static_cast<const AST::LiteralExpression*>(expr));
			break;
		case AST::ExpressionType::IdentifierExpression:
			ValidateIdentifierExpression(static_cast<const AST::IdentifierExpression*>(expr));
			break;
		case AST::ExpressionType::AssignmentExpression:
			ValidateAssignmentExpression(static_cast<const AST::AssignmentExpression*>(expr));
			break;
		case AST::ExpressionType::CallExpression:
			ValidateCallExpression(static_cast<const AST::CallExpression*>(expr));
			break;
		default:
			EYE_LOG_CRITICAL("EYESemantic ValidateExpression Unsupported Expression Type!");
			break;
		}
	}

	void Semantic::ValidateLiteralExpression(const AST::LiteralExpression* literalExpr)
	{
	}

	void Semantic::ValidateIdentifierExpression(const AST::IdentifierExpression* identifierExpr)
	{
		if (!m_DeclarationEnvironment->Has(identifierExpr->GetValue()))
			throw Error::Exceptions::NotDeclaredException("'" + identifierExpr->GetValue() + "' Was Not Declared in this Scope", Error::ErrorType::SemanticNotDeclared, identifierExpr->GetSource());
	}

	void Semantic::ValidateAssignmentExpression(const AST::AssignmentExpression* assignExpr)
	{
		ValidateExpression(assignExpr->GetLHSExpression());

		if (assignExpr->GetLHSExpression()->GetType() == AST::ExpressionType::IdentifierExpression)
		{
			const auto& astIdentifierExpr = static_cast<const AST::IdentifierExpression*>(assignExpr->GetLHSExpression());
			if (m_VariableTypeQualifierEnvironment->Get(astIdentifierExpr->GetValue()) == VariableTypeQualifier::Const)
				throw Error::Exceptions::WriteReadOnlyException("Assignment of Read-Only Variable: '" + astIdentifierExpr->GetValue() + "'", Error::ErrorType::SemanticWriteReadOnly, astIdentifierExpr->GetSource());
		}

		ValidateExpression(assignExpr->GetExpression());
	}

	void Semantic::ValidateCallExpression(const AST::CallExpression* callExpr)
	{
		ValidateExpression(callExpr->GetCallee());

		if (callExpr->GetCallee()->GetType() == AST::ExpressionType::IdentifierExpression)
		{
			const auto& astIdentifierExpr = static_cast<const AST::IdentifierExpression*>(callExpr->GetCallee());

			if (m_DeclarationEnvironment->Get(astIdentifierExpr->GetValue()) == DeclarationType::Variable)
				throw Error::Exceptions::CallException("Cannot Call Variable: '" + astIdentifierExpr->GetValue() + "'", Error::ErrorType::SemanticCallVariable, astIdentifierExpr->GetSource());

			const auto& funcDec = m_FunctionDeclarationEnvironment->Get(astIdentifierExpr->GetValue());
			if (callExpr->GetArguments().size() < funcDec.RequiredParameterCount)
				throw Error::Exceptions::ArgumentException("Too Few Arguments for Function '" + astIdentifierExpr->GetValue() + "'", Error::ErrorType::SemanticTooFewArguments, astIdentifierExpr->GetSource());
			else if (callExpr->GetArguments().size() > funcDec.Parameters.size())
				throw Error::Exceptions::ArgumentException("Too Many Arguments for Function '" + astIdentifierExpr->GetValue() + "'", Error::ErrorType::SemanticTooManyArguments, astIdentifierExpr->GetSource());
		}

		for (const auto& arg : callExpr->GetArguments())
			ValidateExpression(arg.get());
	}

	void Semantic::BeginBlockScope()
	{
		m_DeclarationEnvironment = std::make_shared<MapEnvironment<DeclarationType>>(m_DeclarationEnvironment);
		m_FunctionDeclarationEnvironment = std::make_shared<MapEnvironment<FunctionDeclaration>>(m_FunctionDeclarationEnvironment);
		m_VariableTypeQualifierEnvironment = std::make_shared<MapEnvironment<VariableTypeQualifier>>(m_VariableTypeQualifierEnvironment);
	}

	void Semantic::EndBlockScope()
	{
		m_VariableTypeQualifierEnvironment = m_VariableTypeQualifierEnvironment->GetParent();
		m_FunctionDeclarationEnvironment = m_FunctionDeclarationEnvironment->GetParent();
		m_DeclarationEnvironment = m_DeclarationEnvironment->GetParent();
	}
}
