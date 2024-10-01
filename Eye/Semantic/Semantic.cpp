#include "Eye/Semantic/Semantic.h"
#include "Eye/Utility/Logger.h"
#include "Eye/Error/Exceptions/NotDeclaredException.h"
#include "Eye/Error/Exceptions/ReDeclarationException.h"
#include "Eye/Error/Exceptions/BadDataTypeException.h"
#include "Eye/Error/Exceptions/WriteReadOnlyException.h"
#include "Eye/Error/Exceptions/ReturnException.h"

#include <functional>

namespace Eye
{
	std::expected<bool, Error::Error> Semantic::Validate(const std::shared_ptr<AST::Program>& ast)
	{
		m_DeclarationEnvironment = std::make_shared<MapEnvironment<DeclarationType>>();
		m_VariableTypeQualifierEnvironment = std::make_shared<MapEnvironment<VariableTypeQualifier>>();

		try
		{
			for (const auto& stmt : ast->GetStatementList())
				ValidateStatement(stmt);
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

	void Semantic::ValidateStatement(const std::shared_ptr<AST::Statement>& stmt)
	{
		switch (stmt->GetType())
		{
		case AST::StatementType::ExpressionStatement:
			ValidateExpressionStatement(std::static_pointer_cast<AST::ExpressionStatement>(stmt));
			break;
		case AST::StatementType::BlockStatement:
			ValidateBlockStatement(std::static_pointer_cast<AST::BlockStatement>(stmt));
			break;
		case AST::StatementType::VariableStatement:
			ValidateVariableStatement(std::static_pointer_cast<AST::VariableStatement>(stmt));
			break;
		case AST::StatementType::FunctionStatement:
			ValidateFunctionStatement(std::static_pointer_cast<AST::FunctionStatement>(stmt));
			break;
		case AST::StatementType::ReturnStatement:
			ValidateReturnStatement(std::static_pointer_cast<AST::ReturnStatement>(stmt));
			break;
		default:
			EYE_LOG_CRITICAL("EYESemantic ValidateStatement Unsupported Statement Type!");
			break;
		}
	}

	void Semantic::ValidateExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt)
	{
		ValidateExpression(exprStmt->GetExpression());
	}

	void Semantic::ValidateBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt, bool createScope)
	{
		if (createScope)
			BeginBlockScope();
		for (const auto& stmt : blockStmt->GetStatementList())
			ValidateStatement(stmt);
		if (createScope)
			EndBlockScope();
	}

	void Semantic::ValidateVariableStatement(const std::shared_ptr<AST::VariableStatement>& varStmt)
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

	void Semantic::ValidateFunctionStatement(const std::shared_ptr<AST::FunctionStatement>& functionStmt)
	{
		if (m_DeclarationEnvironment->Has(functionStmt->GetIdentifier()->GetValue()))
			throw Error::Exceptions::ReDeclarationException("ReDeclaration of '" + functionStmt->GetIdentifier()->GetValue() + "'", Error::ErrorType::SemanticReDeclaration, functionStmt->GetIdentifier()->GetSource());
	
		m_DeclarationEnvironment->Define(functionStmt->GetIdentifier()->GetValue(), DeclarationType::Function);

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

	void Semantic::ValidateFunctionReturnStatement(const std::shared_ptr<AST::FunctionStatement>& functionStmt)
	{
		bool functionReturns = (functionStmt->GetReturnType()->GetType() != TokenType::KeywordDataTypeVoid);
		bool foundReturn = false;
	
		std::function<void(const std::shared_ptr<AST::BlockStatement>& block)> validateReturn = [&](const std::shared_ptr<AST::BlockStatement>& block) -> void
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
						validateReturn(std::static_pointer_cast<AST::BlockStatement>(stmt));
					}
				}

				if (functionReturns && !foundReturn)
					throw Error::Exceptions::ReturnException("Non-Void Functions Must Always Return '" + functionStmt->GetIdentifier()->GetValue() + "()'", Error::ErrorType::SemanticNoReturn, functionStmt->GetSource());
			};

		validateReturn(functionStmt->GetBody());
	}

	void Semantic::ValidateReturnStatement(const std::shared_ptr<AST::ReturnStatement>& returnStmt)
	{
		ValidateExpression(returnStmt->GetExpression());
	}

	void Semantic::ValidateExpression(const std::shared_ptr<AST::Expression>& expr)
	{
		switch (expr->GetType())
		{
		case AST::ExpressionType::LiteralExpression:
			ValidateLiteralExpression(std::static_pointer_cast<AST::LiteralExpression>(expr));
			break;
		case AST::ExpressionType::IdentifierExpression:
			ValidateIdentifierExpression(std::static_pointer_cast<AST::IdentifierExpression>(expr));
			break;
		case AST::ExpressionType::AssignmentExpression:
			ValidateAssignmentExpression(std::static_pointer_cast<AST::AssignmentExpression>(expr));
			break;
		case AST::ExpressionType::CallExpression:
			ValidateCallExpression(std::static_pointer_cast<AST::CallExpression>(expr));
			break;
		default:
			EYE_LOG_CRITICAL("EYESemantic ValidateExpression Unsupported Expression Type!");
			break;
		}
	}

	void Semantic::ValidateLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr)
	{
	}

	void Semantic::ValidateIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr)
	{
		if (!m_DeclarationEnvironment->Has(identifierExpr->GetValue()))
			throw Error::Exceptions::NotDeclaredException("'" + identifierExpr->GetValue() + "' Was Not Declared in this Scope", Error::ErrorType::SemanticNotDeclared, identifierExpr->GetSource());
	}

	void Semantic::ValidateAssignmentExpression(const std::shared_ptr<AST::AssignmentExpression>& assignExpr)
	{
		ValidateExpression(assignExpr->GetLHSExpression());

		if (assignExpr->GetLHSExpression()->GetType() == AST::ExpressionType::IdentifierExpression)
		{
			const auto& astIdentifierExpr = std::static_pointer_cast<AST::IdentifierExpression>(assignExpr->GetLHSExpression());
			if (m_VariableTypeQualifierEnvironment->Get(astIdentifierExpr->GetValue()) == VariableTypeQualifier::Const)
				throw Error::Exceptions::WriteReadOnlyException("Assignment of Read-Only Variable: '" + astIdentifierExpr->GetValue() + "'", Error::ErrorType::SemanticWriteReadOnly, astIdentifierExpr->GetSource());
		}

		ValidateExpression(assignExpr->GetExpression());
	}

	void Semantic::ValidateCallExpression(const std::shared_ptr<AST::CallExpression>& callExpr)
	{
		if (callExpr->GetCallee()->GetType() == AST::ExpressionType::IdentifierExpression)
		{
			const auto& astIdentifierExpr = std::static_pointer_cast<AST::IdentifierExpression>(callExpr->GetCallee());
			if (!m_DeclarationEnvironment->Has(astIdentifierExpr->GetValue()))
				throw Error::Exceptions::NotDeclaredException("'" + astIdentifierExpr->GetValue() + "()' Was Not Declared in this Scope", Error::ErrorType::SemanticNotDeclared, astIdentifierExpr->GetSource());
		}
	}

	void Semantic::BeginBlockScope()
	{
		m_DeclarationEnvironment = std::make_shared<MapEnvironment<DeclarationType>>(m_DeclarationEnvironment);
		m_VariableTypeQualifierEnvironment = std::make_shared<MapEnvironment<VariableTypeQualifier>>(m_VariableTypeQualifierEnvironment);
	}

	void Semantic::EndBlockScope()
	{
		m_VariableTypeQualifierEnvironment = m_VariableTypeQualifierEnvironment->GetParent();
		m_DeclarationEnvironment = m_DeclarationEnvironment->GetParent();
	}
}
