#include "EYEASTSerializer/StringSerializer.h"

#include <EYEUtility/Logger.h>

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
			switch (stmt->GetType())
			{
			case AST::StatementType::ExpressionStatement:
				return SerializeExpressionStatement(std::static_pointer_cast<AST::ExpressionStatement>(stmt));
			case AST::StatementType::BlockStatement:
				return SerializeBlockStatement(std::static_pointer_cast<AST::BlockStatement>(stmt));
			case AST::StatementType::VariableStatement:
				return SerializeVariableStatement(std::static_pointer_cast<AST::VariableStatement>(stmt));
			case AST::StatementType::ControlStatement:
				return SerializeControlStatement(std::static_pointer_cast<AST::ControlStatement>(stmt));
			case AST::StatementType::IterationStatement:
				return SerializeIterationStatement(std::static_pointer_cast<AST::IterationStatement>(stmt));
			case AST::StatementType::FunctionStatement:
				return SerializeFunctionStatement(std::static_pointer_cast<AST::FunctionStatement>(stmt));
			case AST::StatementType::ReturnStatement:
				return SerializeReturnStatement(std::static_pointer_cast<AST::ReturnStatement>(stmt));
			case AST::StatementType::StructStatement:
				return SerializeStructStatement(std::static_pointer_cast<AST::StructStatement>(stmt));
			default:
				EYE_LOG_CRITICAL("ASTSerializer Unknown Statement Type!");
				break;
			}
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

		std::string StringSerializer::SerializeBlockStatement(const std::shared_ptr<AST::BlockStatement>& blockStmt)
		{
			std::ostringstream oss;
			oss << "{\"BlockStatement\": {\n";
			oss << "\"type\": \"BlockStatement\",\n";
			oss << "\"StatementListSize\": " << blockStmt->GetStatementList().size() << ",\n";
			oss << "\"StatementList\": [\n";
			size_t i = 0;
			for (const auto& stmt : blockStmt->GetStatementList())
			{
				oss << "" << SerializeStatement(stmt);

				i++;
				if ((i + 1) <= blockStmt->GetStatementList().size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeVariableStatement(const std::shared_ptr<AST::VariableStatement>& variableStmt)
		{
			std::ostringstream oss;
			oss << "{\"VariableStatement\": {\n";
			oss << "\"type\": \"VariableStatement\",\n";
			oss << "\"dataType\": \"" << Lexer::TokenTypeStr[(int)variableStmt->GetDataType().GetType()] << "\",\n";
			oss << "\"declarationSize\": " << variableStmt->GetVariableDeclarationList().size() << ",\n";
			oss << "\"declarations\": [\n";
			size_t i = 0;
			for (const auto& variable : variableStmt->GetVariableDeclarationList())
			{
				oss << SerializeVariableDeclaration(variable);
				i++;
				if ((i + 1) <= variableStmt->GetVariableDeclarationList().size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeVariableDeclaration(const std::shared_ptr<AST::VariableDeclaration>& variableDeclaration)
		{
			std::ostringstream oss;
			oss << "{\"VariableDeclaration\": {\n";
			oss << "\"type\": \"VariableDeclaration\",\n";
			oss << "\"identifier\":" << SerializeIdentifierExpression(variableDeclaration->GetIdentifier()) << ",\n";

			if (variableDeclaration->GetInitializer())
				oss << "\"initializer\":" << SerializeExpression(variableDeclaration->GetInitializer()) << "\n";
			else
				oss << "\"initializer\":" << "null" << "\n";

			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeControlStatement(const std::shared_ptr<AST::ControlStatement>& controlStmt)
		{
			std::ostringstream oss;
			oss << "{\"ControlStatement\": {\n";
			oss << "\"type\": \"ControlStatement\",\n";
			oss << "\"condition\": " << SerializeExpression(controlStmt->GetCondition()) << ",\n";
			oss << "\"consequent\": " << SerializeStatement(controlStmt->GetConsequent()) << ",\n";
			if (controlStmt->GetAlternate())
				oss << "\"alternate\": " << SerializeStatement(controlStmt->GetAlternate()) << "\n";
			else
				oss << "\"alternate\": null\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeIterationStatement(const std::shared_ptr<AST::IterationStatement>& iterationStmt)
		{
			switch (iterationStmt->GetIterationType())
			{
			case AST::IterationStatementType::WhileStatement:
				return SerializeWhileStatement(std::static_pointer_cast<AST::WhileStatement>(iterationStmt));
			case AST::IterationStatementType::DoWhileStatement:
				return SerializeDoWhileStatement(std::static_pointer_cast<AST::DoWhileStatement>(iterationStmt));
			case AST::IterationStatementType::ForStatement:
				return SerializeForStatement(std::static_pointer_cast<AST::ForStatement>(iterationStmt));
			default:
				break;
			}
		}

		std::string StringSerializer::SerializeWhileStatement(const std::shared_ptr<AST::WhileStatement>& whileStmt)
		{
			std::ostringstream oss;
			oss << "{\"WhileStatement\": {\n";
			oss << "\"type\": \"WhileStatement\",\n";
			oss << "\"condition\": " << SerializeExpression(whileStmt->GetCondition()) << ",\n";
			oss << "\"body\": " << SerializeStatement(whileStmt->GetBody()) << "\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeDoWhileStatement(const std::shared_ptr<AST::DoWhileStatement>& doWhileStmt)
		{
			std::ostringstream oss;
			oss << "{\"DoWhileStatement\": {\n";
			oss << "\"type\": \"DoWhileStatement\",\n";
			oss << "\"condition\": " << SerializeExpression(doWhileStmt->GetCondition()) << ",\n";
			oss << "\"body\": " << SerializeStatement(doWhileStmt->GetBody()) << "\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeForStatement(const std::shared_ptr<AST::ForStatement>& forStmt)
		{
			std::ostringstream oss;
			oss << "{\"ForStatement\": {\n";
			oss << "\"type\": \"ForStatement\",\n";
			if (forStmt->GetInitializerType() == AST::ForInitializerType::VariableStatement)
				oss << "\"initializer\": " << SerializeVariableStatement(forStmt->GetInitializer<AST::VariableStatement>()) << ",\n";
			else if (forStmt->GetInitializerType() == AST::ForInitializerType::Expression)
				oss << "\"initializer\": " << SerializeExpression(forStmt->GetInitializer<AST::Expression>()) << ",\n";
			else
				oss << "\"initializer\":" << "null" << ",\n";

			if (forStmt->GetCondition())
				oss << "\"condition\": " << SerializeExpression(forStmt->GetCondition()) << ",\n";
			else
				oss << "\"condition\":" << "null" << ",\n";

			if (forStmt->GetUpdate())
				oss << "\"update\": " << SerializeExpression(forStmt->GetUpdate()) << ",\n";
			else
				oss << "\"update\":" << "null" << ",\n";

			if (forStmt->GetBody())
				oss << "\"body\": " << SerializeStatement(forStmt->GetBody()) << "\n";
			else
				oss << "\"body\": " << "null" << "\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeFunctionStatement(const std::shared_ptr<AST::FunctionStatement>& functionStmt)
		{
			std::ostringstream oss;
			oss << "{\"FunctionStatement\": {\n";
			oss << "\"type\": \"FunctionStatement\",\n";
			oss << "\"returnType\": \"" << Lexer::TokenTypeStr[(int)functionStmt->GetReturnType().GetType()] << "\",\n";
			oss << "\"identifier\": " << SerializeIdentifierExpression(functionStmt->GetIdentifier()) << ",\n";
			oss << "\"parameters\": [\n";
			size_t i = 0;
			for (const auto& param : functionStmt->GetParameters())
			{
				oss << SerializeFunctionParameter(param);
				i++;
				if ((i + 1) <= functionStmt->GetParameters().size())
					oss << ",";
			}
			oss << "],\n";
			oss << "\"body\": " << SerializeBlockStatement(functionStmt->GetBody()) << "\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeFunctionParameter(const std::shared_ptr<AST::FunctionParameter>& functionParam)
		{
			std::ostringstream oss;
			oss << "{\"FunctionParameter\": {\n";
			oss << "\"type\": \"FunctionParameter\",\n";
			oss << "\"dataType\": \"" << Lexer::TokenTypeStr[(int)functionParam->GetDataType().GetType()] << "\",\n";
			oss << "\"identifier\":" << SerializeIdentifierExpression(functionParam->GetIdentifier()) << ",\n";

			if (functionParam->GetInitializer())
				oss << "\"initializer\":" << SerializeExpression(functionParam->GetInitializer()) << "\n";
			else
				oss << "\"initializer\":" << "null" << "\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeReturnStatement(const std::shared_ptr<AST::ReturnStatement>& returnStmt)
		{
			std::ostringstream oss;
			oss << "{\"ReturnStatement\": {\n";
			oss << "\"type\": \"ReturnStatement\",\n";
			if (returnStmt->GetExpression())
				oss << "\"expression\": " << SerializeExpression(returnStmt->GetExpression()) << "\n";
			else
				oss << "\"expression\":" << "null\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeStructStatement(const std::shared_ptr<AST::StructStatement>& structStmt)
		{
			std::ostringstream oss;
			oss << "{\"StructStatement\": {\n";
			oss << "\"type\": \"StructStatement\",\n";
			oss << "\"identifier\": " << SerializeIdentifierExpression(structStmt->GetIdentifier()) << ",\n";
			oss << "\"members\": [\n";
			size_t i = 0;
			for (const auto& member : structStmt->GetMembers())
			{
				oss << SerializeVariableStatement(member);
				i++;
				if ((i + 1) <= structStmt->GetMembers().size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeExpression(const std::shared_ptr<AST::Expression>& expr)
		{
			if (expr->GetType() == AST::ExpressionType::LiteralExpression)
				return SerializeLiteralExpression(std::static_pointer_cast<AST::LiteralExpression>(expr));
			else if (expr->GetType() == AST::ExpressionType::BinaryExpression)
				return SerializeBinaryExpression(std::static_pointer_cast<AST::BinaryExpression>(expr));
			else if (expr->GetType() == AST::ExpressionType::IdentifierExpression)
				return SerializeIdentifierExpression(std::static_pointer_cast<AST::IdentifierExpression>(expr));
			else if (expr->GetType() == AST::ExpressionType::AssignmentExpression)
				return SerializeAssignmentExpression(std::static_pointer_cast<AST::AssignmentExpression>(expr));
			else if (expr->GetType() == AST::ExpressionType::UnaryExpression)
				return SerializeUnaryExpression(std::static_pointer_cast<AST::UnaryExpression>(expr));
			else if (expr->GetType() == AST::ExpressionType::MemberExpression)
				return SerializeMemberExpression(std::static_pointer_cast<AST::MemberExpression>(expr));
			else if (expr->GetType() == AST::ExpressionType::CallExpression)
				return SerializeCallExpression(std::static_pointer_cast<AST::CallExpression>(expr));
			else if (expr->GetType() == AST::ExpressionType::PostfixExpression)
				return SerializePostfixExpression(std::static_pointer_cast<AST::PostfixExpression>(expr));
			else
				EYE_LOG_CRITICAL("ASTSerializer Unknown Expression Type!");
		}

		std::string StringSerializer::SerializeLiteralExpression(const std::shared_ptr<AST::LiteralExpression>& literalExpr)
		{
			std::ostringstream oss;
			oss << "{\"LiteralExpression\": {\n";
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

		std::string StringSerializer::SerializeIdentifierExpression(const std::shared_ptr<AST::IdentifierExpression>& identifierExpr)
		{
			std::ostringstream oss;
			oss << "{\"IdentifierExpression\": {\n";
			oss << "\"type\": \"IdentifierExpression\",\n";
			oss << "\"value\": \"" << identifierExpr->GetValue() << "\"\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeAssignmentExpression(const std::shared_ptr<AST::AssignmentExpression>& assignmentExpr)
		{
			std::ostringstream oss;
			oss << "{\"AssignmentExpression\": {\n";
			oss << "\"type\": \"AssignmentExpression\",\n";
			oss << "\"operator\": \"" << Lexer::TokenTypeStr[(int)assignmentExpr->GetOperator().GetType()] << "\",\n";
			oss << "\"lhsExpression\": " << SerializeExpression(assignmentExpr->GetLHSExpression()) << ",\n";
			oss << "\"expression\": " << SerializeExpression(assignmentExpr->GetExpression()) << "\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeUnaryExpression(const std::shared_ptr<AST::UnaryExpression>& unaryExpr)
		{
			std::ostringstream oss;
			oss << "{\"UnaryExpression\": {\n";
			oss << "\"type\": \"UnaryExpression\",\n";
			oss << "\"operator\": \"" << Lexer::TokenTypeStr[(int)unaryExpr->GetOperator().GetType()] << "\",\n";
			oss << "\"expression\": " << SerializeExpression(unaryExpr->GetExpression()) << "\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeMemberExpression(const std::shared_ptr<AST::MemberExpression>& memberExpr)
		{
			std::ostringstream oss;
			oss << "{\"MemberExpression\": {\n";
			oss << "\"type\": \"MemberExpression\",\n";
			oss << "\"object\":" << SerializeExpression(memberExpr->GetObject()) << ",\n";
			oss << "\"property\":" << SerializeExpression(memberExpr->GetProperty()) << ",\n";
			oss << "\"computed\": " << (memberExpr->IsComputed() ? "true" : "false") << "\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeCallExpression(const std::shared_ptr<AST::CallExpression>& callExpr)
		{
			std::ostringstream oss;
			oss << "{\"CallExpression\": {\n";
			oss << "\"type\": \"CallExpression\",\n";
			oss << "\"callee\": " << SerializeExpression(callExpr->GetCallee()) << ",\n";
			oss << "\"arguments\": [\n";
			size_t i = 0;
			for (const auto& arg : callExpr->GetArguments())
			{
				oss << SerializeExpression(arg);
				i++;
				if ((i + 1) <= callExpr->GetArguments().size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializePostfixExpression(const std::shared_ptr<AST::PostfixExpression>& postfixExpr)
		{
			std::ostringstream oss;
			oss << "{\"PostfixExpression\": {\n";
			oss << "\"type\": \"PostfixExpression\",\n";
			oss << "\"operator\": \"" << Lexer::TokenTypeStr[(int)postfixExpr->GetOperator().GetType()] << "\",\n";
			oss << "\"expression\": " << SerializeExpression(postfixExpr->GetExpression()) << "\n";
			oss << "}\n}";
			return oss.str();
		}
	}
}
