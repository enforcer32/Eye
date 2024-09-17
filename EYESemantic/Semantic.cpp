#include "EYESemantic/Semantic.h"

#include <EYEUtility/Logger.h>
#include <EYEError/Exceptions/NotDeclaredException.h>
#include <EYEError/Exceptions/ReDeclarationException.h>
#include <EYEError/Exceptions/BadDataTypeException.h>

namespace Eye
{
	namespace Semantic
	{
		std::expected<bool, Error::Error> Semantic::Validate(const std::shared_ptr<AST::Program>& ast)
		{
			m_VariableEnvironment = std::make_shared<Environment<std::string>>();

			try
			{
				for (const auto& stmt : ast->GetStatementList())
					ValidateStatement(stmt);
			}
			catch (const Error::Exceptions::NotDeclaredException& ex)
			{
				return std::unexpected(Error::Error(Error::ErrorType::SemanticNotDeclared, ex.what()));
			}
			catch (const Error::Exceptions::ReDeclarationException& ex)
			{
				return std::unexpected(Error::Error(Error::ErrorType::SemanticReDeclaration, ex.what()));
			}
			catch (const Error::Exceptions::BadDataTypeException& ex)
			{
				return std::unexpected(Error::Error(Error::ErrorType::SemanticBadDataType, ex.what()));
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
			if (varStmt->GetDataType()->GetType() == Lexer::TokenType::KeywordDataTypeVoid)
				throw Error::Exceptions::BadDataTypeException("Variable Declared as void", varStmt->GetSource());

			for (const auto& var : varStmt->GetVariableDeclarationList())
			{
				if (m_VariableEnvironment->Has(var->GetIdentifier()->GetValue()))
					throw Error::Exceptions::ReDeclarationException("ReDeclaration of '" + var->GetIdentifier()->GetValue() + "'", var->GetIdentifier()->GetSource());

				if (var->GetInitializer())
					ValidateExpression(var->GetInitializer());

				m_VariableEnvironment->Define(var->GetIdentifier()->GetValue());
			}
		}

		void Semantic::ValidateExpression(const std::shared_ptr<AST::Expression>& expr)
		{
			switch (expr->GetType())
			{
			case AST::ExpressionType::IdentifierExpression:
				ValidateIdentifierExpression(std::static_pointer_cast<AST::IdentifierExpression>(expr));
				break;
			default:
				EYE_LOG_CRITICAL("EYESemantic ValidateExpression Unsupported Expression Type!");
				break;
			}
		}

		void Semantic::ValidateIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr)
		{
			if (!m_VariableEnvironment->Has(identifierExpr->GetValue()))
				throw Error::Exceptions::NotDeclaredException("'" + identifierExpr->GetValue() + "' Was Not Declared in this Scope", identifierExpr->GetSource());
		}

		void Semantic::BeginBlockScope()
		{
			m_VariableEnvironment = std::make_shared<Environment<std::string>>(m_VariableEnvironment);
		}

		void Semantic::EndBlockScope()
		{
			m_VariableEnvironment = m_VariableEnvironment->GetParent();
		}
	}
}
