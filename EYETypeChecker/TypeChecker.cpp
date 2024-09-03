#include "EYETypeChecker/TypeChecker.h"

#include <EYEUtility/Logger.h>

namespace Eye
{
	namespace TypeChecker
	{
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
				if ((leftType == Type::Integer || leftType == Type::Float) && (rightType != Type::Integer && rightType != Type::Float))
				{
					if (rightType == Type::String)
					{
						std::string value = std::static_pointer_cast<AST::LiteralExpression>(binaryExpr->GetRight())->GetValue<AST::LiteralStringType>();
						EYE_LOG_CRITICAL("TYPEChecker Binary(+)->Expected Integer/Float Type for (\"{}\") but got {} Type Instead!", value, TypeToString(rightType));
					}
					else if (rightType == Type::Boolean)
					{
						std::string value = (std::static_pointer_cast<AST::LiteralExpression>(binaryExpr->GetRight())->GetValue<AST::LiteralBooleanType>() ? "true" : "false");
						EYE_LOG_CRITICAL("TYPEChecker Binary(+)->Expected Integer/Float for Type ({}) but got {} Type Instead!", value, TypeToString(rightType));
					}
				}
				return leftType;
			}
		}
	}
}
