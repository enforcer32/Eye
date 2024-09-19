#include "EYESemantic/Semantic.h"

#include <EYEUtility/Logger.h>
#include <EYEError/Exceptions/NotDeclaredException.h>
#include <EYEError/Exceptions/ReDeclarationException.h>
#include <EYEError/Exceptions/BadDataTypeException.h>
#include <EYEError/Exceptions/WriteReadOnlyException.h>

namespace Eye
{
	namespace Semantic
	{
		std::expected<bool, Error::Error> Semantic::Validate(const std::shared_ptr<AST::Program>& ast)
		{
			m_VariableEnvironment = std::make_shared<SetEnvironment<std::string>>();
			m_VariableTypeQualifierEnvironment = std::make_shared<MapEnvironment<VariableTypeQualifier>>();

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
			catch (const Error::Exceptions::WriteReadOnlyException& ex)
			{
				return std::unexpected(Error::Error(Error::ErrorType::SemanticWriteReadOnly, ex.what()));
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

			VariableTypeQualifier typeQualifier = VariableTypeQualifier::None;
			if (varStmt->GetTypeQualifier() && varStmt->GetTypeQualifier()->GetType() == Lexer::TokenType::KeywordTypeQualifierConst)
				typeQualifier = VariableTypeQualifier::Const;

			for (const auto& var : varStmt->GetVariableDeclarationList())
			{
				if (m_VariableEnvironment->Has(var->GetIdentifier()->GetValue()))
					throw Error::Exceptions::ReDeclarationException("ReDeclaration of '" + var->GetIdentifier()->GetValue() + "'", var->GetIdentifier()->GetSource());

				if (var->GetInitializer())
					ValidateExpression(var->GetInitializer());

				m_VariableEnvironment->Define(var->GetIdentifier()->GetValue());
				m_VariableTypeQualifierEnvironment->Define(var->GetIdentifier()->GetValue(), typeQualifier);
			}
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
			if (!m_VariableEnvironment->Has(identifierExpr->GetValue()))
				throw Error::Exceptions::NotDeclaredException("'" + identifierExpr->GetValue() + "' Was Not Declared in this Scope", identifierExpr->GetSource());
		}

		void Semantic::ValidateAssignmentExpression(const std::shared_ptr<AST::AssignmentExpression>& assignExpr)
		{
			if (assignExpr->GetLHSExpression()->GetType() == AST::ExpressionType::IdentifierExpression)
			{
				const auto& astIdentifierExpr = std::static_pointer_cast<AST::IdentifierExpression>(assignExpr->GetLHSExpression());
				if (m_VariableTypeQualifierEnvironment->Get(astIdentifierExpr->GetValue()) == VariableTypeQualifier::Const)
					throw Error::Exceptions::WriteReadOnlyException("Assignment of Read-Only Variable: '" + astIdentifierExpr->GetValue() + "'", astIdentifierExpr->GetSource());
			}

			ValidateExpression(assignExpr->GetLHSExpression());
			ValidateExpression(assignExpr->GetExpression());
		}

		void Semantic::BeginBlockScope()
		{
			m_VariableEnvironment = std::make_shared<SetEnvironment<std::string>>(m_VariableEnvironment);
			m_VariableTypeQualifierEnvironment = std::make_shared<MapEnvironment<VariableTypeQualifier>>();
		}

		void Semantic::EndBlockScope()
		{
			m_VariableTypeQualifierEnvironment = m_VariableTypeQualifierEnvironment->GetParent();
			m_VariableEnvironment = m_VariableEnvironment->GetParent();
		}
	}
}
