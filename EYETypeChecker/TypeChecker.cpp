#include "EYETypeChecker/TypeChecker.h"

#include <EYEUtility/Logger.h>

namespace Eye
{
	namespace TypeChecker
	{
		bool TypeChecker::TypeCheck(const std::shared_ptr<AST::Program>& ast)
		{
			m_TypeEnvironment = std::make_shared<TypeEnvironment>();
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
			case AST::StatementType::BlockStatement:
				TypeCheckBlockStatement(std::static_pointer_cast<AST::BlockStatement>(stmt));
				break;
			case AST::StatementType::VariableStatement:
				TypeCheckVariableStatement(std::static_pointer_cast<AST::VariableStatement>(stmt));
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

		void TypeChecker::TypeCheckVariableStatement(const std::shared_ptr<AST::VariableStatement>& varStmt)
		{
			Type variableType = LexerToTypeCheckerType(varStmt->GetDataType()->GetType());
			
			for (const auto& var : varStmt->GetVariableDeclarationList())
			{
				if (var->GetInitializer())
				{
					Type initializerType = TypeCheckExpression(var->GetInitializer());
					if (variableType != initializerType)
						EYE_LOG_CRITICAL("EYETypeChecker Variable Declaration->Expected {} Type for (\"{}\") but got {} Type Instead!", TypeToString(variableType), var->GetIdentifier()->GetValue(), TypeToString(initializerType));
				}
				m_TypeEnvironment->DefineVariable(var->GetIdentifier()->GetValue(), variableType);
			}
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
			
			if (binaryExpr->GetOperator()->GetType() == Lexer::TokenType::OperatorBinaryPlus)
			{
				if ((leftType == Type::Integer || leftType == Type::Float) && (rightType != Type::Integer && rightType != Type::Float))
				{
					if (rightType == Type::String)
					{
						std::string value = std::static_pointer_cast<AST::LiteralExpression>(binaryExpr->GetRight())->GetValue<AST::LiteralStringType>();
						EYE_LOG_CRITICAL("EYETypeChecker Binary(+)->Expected Integer/Float Type for (\"{}\") but got {} Type Instead!", value, TypeToString(rightType));
					}
					else if (rightType == Type::Boolean)
					{
						std::string value = (std::static_pointer_cast<AST::LiteralExpression>(binaryExpr->GetRight())->GetValue<AST::LiteralBooleanType>() ? "true" : "false");
						EYE_LOG_CRITICAL("EYETypeChecker Binary(+)->Expected Integer/Float for Type ({}) but got {} Type Instead!", value, TypeToString(rightType));
					}
				}
				return leftType;
			}
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
			return Type::Invalid;
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
