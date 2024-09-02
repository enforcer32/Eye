#include "EYETypeChecker/TypeChecker.h"

#include <EYEUtility/Logger.h>

namespace Eye
{
	namespace TypeChecker
	{
		std::string TypeToString(Type type)
		{
			switch (type)
			{
			case Eye::TypeChecker::Type::Integer:
				return "Integer";
				break;
			case Eye::TypeChecker::Type::Float:
				return "Float";
				break;
			case Eye::TypeChecker::Type::String:
				return "String";
				break;
			case Eye::TypeChecker::Type::Boolean:
				return "Boolean";
				break;
			default:
				EYE_LOG_CRITICAL("TypeToString Unknown Type!");
				break;
			}
		}

		bool TypeChecker::TypeCheck(const std::shared_ptr<AST::Program>& ast)
		{
			for (const auto& stmt : ast->GetStatementList())
				TypeCheckStatement(stmt);
			return true;
		}

		void TypeChecker::TypeCheckStatement(const std::shared_ptr<AST::Statement>& stmt)
		{
			switch (stmt->GetType())
			{
			case AST::StatementType::ExpressionStatement:
				TypeCheckExpressionStatement(std::static_pointer_cast<AST::ExpressionStatement>(stmt));
				break;
			default:
				EYE_LOG_CRITICAL("TYPEChecker Unknown Statement Type!");
				break;
			}
		}

		void TypeChecker::TypeCheckExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt)
		{
			TypeCheckExpression(exprStmt->GetExpression());
		}

		Type TypeChecker::TypeCheckExpression(const std::shared_ptr<AST::Expression>& expr)
		{
			switch (expr->GetType())	
			{
			case AST::ExpressionType::LiteralExpression:
				return TypeCheckLiteralExpression(std::static_pointer_cast<AST::LiteralExpression>(expr));
			case AST::ExpressionType::BinaryExpression:
				return TypeCheckBinaryExpression(std::static_pointer_cast<AST::BinaryExpression>(expr));
			default:
				EYE_LOG_CRITICAL("TYPEChecker Unknown Expression Type!");
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
				EYE_LOG_CRITICAL("TYPEChecker Unknown Type!");
				break;
			}
		}

		Type TypeChecker::TypeCheckBinaryExpression(const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
		{
			Type leftType = TypeCheckExpression(binaryExpr->GetLeft());
			Type rightType = TypeCheckExpression(binaryExpr->GetRight());
			
			if (binaryExpr->GetOperator()->GetType() == Lexer::TokenType::OperatorBinaryPlus)
			{
				if (leftType != rightType)
					EYE_LOG_CRITICAL("TYPEChecker Binary(+) Left and Right Types Not Equal!");
				return leftType;
			}
		}
	}
}
