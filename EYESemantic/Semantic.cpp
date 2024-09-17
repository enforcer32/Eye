#include "EYESemantic/Semantic.h"

#include <EYEUtility/Logger.h>
#include <EYEError/Exceptions/NotDeclaredException.h>

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
			default:
				EYE_LOG_CRITICAL("EYETypeChecker Unsupported Statement Type!");
				break;
			}
		}

		void Semantic::ValidateExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt)
		{
			ValidateExpression(exprStmt->GetExpression());
		}

		void Semantic::ValidateExpression(const std::shared_ptr<AST::Expression>& expr)
		{
			switch (expr->GetType())
			{
			case AST::ExpressionType::IdentifierExpression:
				ValidateIdentifierExpression(std::static_pointer_cast<AST::IdentifierExpression>(expr));
				break;
			default:
				EYE_LOG_CRITICAL("EYETypeChecker TypeCheckExpression Unsupported Expression Type!");
				break;
			}
		}

		void Semantic::ValidateIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr)
		{
			if (!m_VariableEnvironment->Has(identifierExpr->GetValue()))
				throw Error::Exceptions::NotDeclaredException("'" + identifierExpr->GetValue() + "' Was Not Declared in this Scope", identifierExpr->GetSource());
		}
	}
}
