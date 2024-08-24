#include "EYEASTSerializer/StringSerializer.h"

#include <sstream>

namespace Eye
{
	namespace ASTSerializer
	{
		std::string StringSerializer::Serialize(const std::shared_ptr<AST::Program>& ast)
		{
			std::ostringstream oss;
			oss << "{\"Program\": {\n";
			oss << "\"type\": \"Program\",\n";
			oss << "\"StatementListSize\": " << ast->GetStatementList().size() << ",\n";
			oss << "\"StatementList\": [\n";
			size_t i = 0;
			for (const auto& stmt : ast->GetStatementList())
			{
				oss << SerializeStatement(stmt);
				i++;
				if ((i + 1) <= ast->GetStatementList().size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeStatement(const std::shared_ptr<AST::Statement>& stmt)
		{
			if (stmt->GetType() == AST::StatementType::ExpressionStatement)
				return SerializeExpressionStatement(std::static_pointer_cast<AST::ExpressionStatement>(stmt));
		}

		std::string StringSerializer::SerializeExpressionStatement(const std::shared_ptr<AST::ExpressionStatement>& exprStmt)
		{
			std::ostringstream oss;
			oss << "{\"ExpressionStatement\": {\n";
			oss << "\"type\": \"ExpressionStatement\",\n";
			oss << "\"expression\": " << SerializeExpression(exprStmt->GetExpression()) << std::endl;
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeExpression(const std::shared_ptr<AST::Expression>& expr)
		{
			if (expr->GetType() == AST::ExpressionType::LiteralExpression)
				return SerializeLiteralExpression(std::static_pointer_cast<AST::LiteralExpression>(expr));
			else if (expr->GetType() == AST::ExpressionType::BinaryExpression)
				return SerializeBinaryExpression(std::static_pointer_cast<AST::BinaryExpression>(expr));
		}

		std::string StringSerializer::SerializeLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr)
		{
			std::ostringstream oss;
			oss << "{\"Literal\": {\n";
			if (literalExpr->GetLiteralType() == AST::LiteralType::Integer)
			{
				oss << "\"type\": \"Integer\",\n";
				oss << "\"value\": " << literalExpr->GetValue<AST::LiteralIntegerType>() << "\n";
			}
			else if (literalExpr->GetLiteralType() == AST::LiteralType::Float)
			{
				oss << "\"type\": \"Float\",\n";
				oss << "\"value\": " << literalExpr->GetValue<AST::LiteralFloatType>() << "\n";
			}
			else if (literalExpr->GetLiteralType() == AST::LiteralType::String)
			{
				oss << "\"type\": \"String\",\n";
				oss << "\"value\": " << "\"" << literalExpr->GetValue<AST::LiteralStringType>() << "\"\n";
			}
			else if (literalExpr->GetLiteralType() == AST::LiteralType::Boolean)
			{
				oss << "\"type\": \"Boolean\",\n";
				oss << "\"value\": " << (literalExpr->GetValue<AST::LiteralBooleanType>()  ? "true" : "false") << "\n";
			}
			else if (literalExpr->GetLiteralType() == AST::LiteralType::Null)
			{
				oss << "\"type\": \"Null\",\n";
				oss << "\"value\": null\n";
			}
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeBinaryExpression(const std::shared_ptr<AST::BinaryExpression>& binaryExpr)
		{
			std::ostringstream oss;
			oss << "{\"BinaryExpression\": {\n";
			oss << "\"type\": \"BinaryExpression\",\n";
			oss << "\"operator\": \"" << Lexer::TokenTypeStr[(int)binaryExpr->GetOperator().GetType()] << "\",\n";
			oss << "\"left\": " << SerializeExpression(binaryExpr->GetLeft()) << ",\n";
			oss << "\"right\": " << SerializeExpression(binaryExpr->GetRight()) << "\n";
			oss << "}\n}";
			return oss.str();
		}
	}
}
