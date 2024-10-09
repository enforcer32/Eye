#include "Eye/ASTSerializer/StringSerializer.h"
#include "Eye/Utility/Logger.h"

#include <sstream>

namespace Eye
{
	namespace ASTSerializer
	{
		std::string StringSerializer::Serialize(const AST::Program* ast)
		{
			std::ostringstream oss;
			oss << "{\"Program\": {\n";
			oss << "\"type\": \"Program\",\n";
			oss << "\"StatementListSize\": " << ast->GetStatementList().size() << ",\n";
			oss << "\"StatementList\": [\n";
			size_t i = 0;
			for (const auto& stmt : ast->GetStatementList())
			{
				oss << SerializeStatement(stmt.get());
				i++;
				if ((i + 1) <= ast->GetStatementList().size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeStatement(const AST::Statement* stmt)
		{
			if (!stmt)
				return "null";

			switch (stmt->GetType())
			{
			case AST::StatementType::ExpressionStatement:
				return SerializeExpressionStatement(static_cast<const AST::ExpressionStatement*>(stmt));
			case AST::StatementType::BlockStatement:
				return SerializeBlockStatement(static_cast<const AST::BlockStatement*>(stmt));
			case AST::StatementType::VariableStatement:
				return SerializeVariableStatement(static_cast<const AST::VariableStatement*>(stmt));
			case AST::StatementType::ControlStatement:
				return SerializeControlStatement(static_cast<const AST::ControlStatement*>(stmt));
			case AST::StatementType::IterationStatement:
				return SerializeIterationStatement(static_cast<const AST::IterationStatement*>(stmt));
			case AST::StatementType::ContinueStatement:
				return SerializeContinueStatement(static_cast<const AST::ContinueStatement*>(stmt));
			case AST::StatementType::BreakStatement:
				return SerializeBreakStatement(static_cast<const AST::BreakStatement*>(stmt));
			case AST::StatementType::FunctionStatement:
				return SerializeFunctionStatement(static_cast<const AST::FunctionStatement*>(stmt));
			case AST::StatementType::ReturnStatement:
				return SerializeReturnStatement(static_cast<const AST::ReturnStatement*>(stmt));
			default:
				EYE_LOG_CRITICAL("ASTSerializer Unknown Statement Type!");
				break;
			}
		}

		std::string StringSerializer::SerializeExpressionStatement(const AST::ExpressionStatement* exprStmt)
		{
			std::ostringstream oss;
			oss << "{\"ExpressionStatement\": {\n";
			oss << "\"type\": \"ExpressionStatement\",\n";
			oss << "\"expression\": " << SerializeExpression(exprStmt->GetExpression()) << std::endl;
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeBlockStatement(const AST::BlockStatement* blockStmt)
		{
			std::ostringstream oss;
			oss << "{\"BlockStatement\": {\n";
			oss << "\"type\": \"BlockStatement\",\n";
			oss << "\"StatementListSize\": " << blockStmt->GetStatementList().size() << ",\n";
			oss << "\"StatementList\": [\n";
			size_t i = 0;
			for (const auto& stmt : blockStmt->GetStatementList())
			{
				oss << "" << SerializeStatement(stmt.get());

				i++;
				if ((i + 1) <= blockStmt->GetStatementList().size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeVariableStatement(const AST::VariableStatement* variableStmt)
		{
			std::ostringstream oss;
			oss << "{\"VariableStatement\": {\n";
			oss << "\"type\": \"VariableStatement\",\n";
			if (variableStmt->GetTypeQualifier())
				oss << "\"typeQualifier\": \"" << variableStmt->GetTypeQualifier()->GetTypeString() << "\",\n";
			else
				oss << "\"typeQualifier\":" << "null" << ",\n";
			oss << "\"dataType\": \"" << variableStmt->GetDataType()->GetTypeString() << "\",\n";
			oss << "\"declarationSize\": " << variableStmt->GetVariableDeclarationList().size() << ",\n";
			oss << "\"declarations\": [\n";
			size_t i = 0;
			for (const auto& variable : variableStmt->GetVariableDeclarationList())
			{
				oss << SerializeVariableDeclaration(variable.get());
				i++;
				if ((i + 1) <= variableStmt->GetVariableDeclarationList().size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeVariableDeclaration(const AST::VariableDeclaration* variableDeclaration)
		{
			std::ostringstream oss;
			oss << "{\"VariableDeclaration\": {\n";
			oss << "\"type\": \"VariableDeclaration\",\n";
			oss << "\"identifier\":" << SerializeIdentifierExpression(variableDeclaration->GetIdentifier()) << ",\n";
			oss << "\"initializer\":" << SerializeExpression(variableDeclaration->GetInitializer()) << "\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeControlStatement(const AST::ControlStatement* controlStmt)
		{
			std::ostringstream oss;
			oss << "{\"ControlStatement\": {\n";
			oss << "\"type\": \"ControlStatement\",\n";
			oss << "\"condition\": " << SerializeExpression(controlStmt->GetCondition()) << ",\n";
			oss << "\"consequent\": " << SerializeStatement(controlStmt->GetConsequent()) << ",\n";
			oss << "\"alternate\": " << SerializeStatement(controlStmt->GetAlternate()) << "\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeIterationStatement(const AST::IterationStatement* iterationStmt)
		{
			switch (iterationStmt->GetIterationType())
			{
			case AST::IterationStatementType::WhileStatement:
				return SerializeWhileStatement(static_cast<const AST::WhileStatement*>(iterationStmt));
			case AST::IterationStatementType::DoWhileStatement:
				return SerializeDoWhileStatement(static_cast<const AST::DoWhileStatement*>(iterationStmt));
			case AST::IterationStatementType::ForStatement:
				return SerializeForStatement(static_cast<const AST::ForStatement*>(iterationStmt));
			default:
				break;
			}
		}

		std::string StringSerializer::SerializeContinueStatement(const AST::ContinueStatement* continueStmt)
		{
			std::ostringstream oss;
			oss << "{\"ContinueStatement\": {\n";
			oss << "\"type\": \"ContinueStatement\"\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeBreakStatement(const AST::BreakStatement* breakStmt)
		{
			std::ostringstream oss;
			oss << "{\"BreakStatement\": {\n";
			oss << "\"type\": \"BreakStatement\"\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeWhileStatement(const AST::WhileStatement* whileStmt)
		{
			std::ostringstream oss;
			oss << "{\"WhileStatement\": {\n";
			oss << "\"type\": \"WhileStatement\",\n";
			oss << "\"condition\": " << SerializeExpression(whileStmt->GetCondition()) << ",\n";
			oss << "\"body\": " << SerializeStatement(whileStmt->GetBody()) << "\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeDoWhileStatement(const AST::DoWhileStatement* doWhileStmt)
		{
			std::ostringstream oss;
			oss << "{\"DoWhileStatement\": {\n";
			oss << "\"type\": \"DoWhileStatement\",\n";
			oss << "\"condition\": " << SerializeExpression(doWhileStmt->GetCondition()) << ",\n";
			oss << "\"body\": " << SerializeStatement(doWhileStmt->GetBody()) << "\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeForStatement(const AST::ForStatement* forStmt)
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
			oss << "\"condition\": " << SerializeExpression(forStmt->GetCondition()) << ",\n";
			oss << "\"update\": " << SerializeExpression(forStmt->GetUpdate()) << ",\n";
			oss << "\"body\": " << SerializeStatement(forStmt->GetBody()) << "\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeFunctionStatement(const AST::FunctionStatement* functionStmt)
		{
			std::ostringstream oss;
			oss << "{\"FunctionStatement\": {\n";
			oss << "\"type\": \"FunctionStatement\",\n";
			oss << "\"returnType\": \"" << functionStmt->GetReturnType()->GetTypeString() << "\",\n";
			oss << "\"identifier\": " << SerializeIdentifierExpression(functionStmt->GetIdentifier()) << ",\n";
			oss << "\"parameters\": [\n";
			size_t i = 0;
			for (const auto& param : functionStmt->GetParameters())
			{
				oss << SerializeFunctionParameter(param.get());
				i++;
				if ((i + 1) <= functionStmt->GetParameters().size())
					oss << ",";
			}
			oss << "],\n";
			oss << "\"body\": " << SerializeBlockStatement(functionStmt->GetBody()) << "\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeFunctionParameter(const AST::FunctionParameter* functionParam)
		{
			std::ostringstream oss;
			oss << "{\"FunctionParameter\": {\n";
			oss << "\"type\": \"FunctionParameter\",\n";
			if (functionParam->GetTypeQualifier())
				oss << "\"typeQualifier\": \"" << functionParam->GetTypeQualifier()->GetTypeString() << "\",\n";
			else
				oss << "\"typeQualifier\":" << "null" << ",\n";
			oss << "\"dataType\": \"" << functionParam->GetDataType()->GetTypeString() << "\",\n";
			oss << "\"identifier\":" << SerializeIdentifierExpression(functionParam->GetIdentifier()) << ",\n";
			oss << "\"initializer\":" << SerializeExpression(functionParam->GetInitializer()) << "\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeReturnStatement(const AST::ReturnStatement* returnStmt)
		{
			std::ostringstream oss;
			oss << "{\"ReturnStatement\": {\n";
			oss << "\"type\": \"ReturnStatement\",\n";
			oss << "\"expression\": " << SerializeExpression(returnStmt->GetExpression()) << "\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializeExpression(const AST::Expression* expr)
		{
			if (!expr)
				return "null";

			switch (expr->GetType())
			{
			case AST::ExpressionType::LiteralExpression:
				return SerializeLiteralExpression(static_cast<const AST::LiteralExpression*>(expr));
			case AST::ExpressionType::BinaryExpression:
				return SerializeBinaryExpression(static_cast<const AST::BinaryExpression*>(expr));
			case AST::ExpressionType::IdentifierExpression:
				return SerializeIdentifierExpression(static_cast<const AST::IdentifierExpression*>(expr));
			case AST::ExpressionType::AssignmentExpression:
				return SerializeAssignmentExpression(static_cast<const AST::AssignmentExpression*>(expr));
			case AST::ExpressionType::UnaryExpression:
				return SerializeUnaryExpression(static_cast<const AST::UnaryExpression*>(expr));
			case AST::ExpressionType::MemberExpression:
				return SerializeMemberExpression(static_cast<const AST::MemberExpression*>(expr));
			case AST::ExpressionType::CallExpression:
				return SerializeCallExpression(static_cast<const AST::CallExpression*>(expr));
			case AST::ExpressionType::PostfixExpression:
				return SerializePostfixExpression(static_cast<const AST::PostfixExpression*>(expr));
			default:
				EYE_LOG_CRITICAL("ASTSerializer Unknown Expression Type!");
				break;
			}
		}

		std::string StringSerializer::SerializeLiteralExpression(const AST::LiteralExpression* literalExpr)
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
				oss << "\"value\": " << (literalExpr->GetValue<AST::LiteralBooleanType>() ? "true" : "false") << "\n";
			}
			else if (literalExpr->GetLiteralType() == AST::LiteralType::Null)
			{
				oss << "\"type\": \"Null\",\n";
				oss << "\"value\": null\n";
			}
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeBinaryExpression(const AST::BinaryExpression* binaryExpr)
		{
			std::ostringstream oss;
			oss << "{\"BinaryExpression\": {\n";
			oss << "\"type\": \"BinaryExpression\",\n";
			oss << "\"operator\": \"" << binaryExpr->GetOperator()->GetTypeString() << "\",\n";
			oss << "\"left\": " << SerializeExpression(binaryExpr->GetLeft()) << ",\n";
			oss << "\"right\": " << SerializeExpression(binaryExpr->GetRight()) << "\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeIdentifierExpression(const AST::IdentifierExpression* identifierExpr)
		{
			std::ostringstream oss;
			oss << "{\"IdentifierExpression\": {\n";
			oss << "\"type\": \"IdentifierExpression\",\n";
			oss << "\"value\": \"" << identifierExpr->GetValue() << "\"\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeAssignmentExpression(const AST::AssignmentExpression* assignmentExpr)
		{
			std::ostringstream oss;
			oss << "{\"AssignmentExpression\": {\n";
			oss << "\"type\": \"AssignmentExpression\",\n";
			oss << "\"operator\": \"" << assignmentExpr->GetOperator()->GetTypeString() << "\",\n";
			oss << "\"lhsExpression\": " << SerializeExpression(assignmentExpr->GetLHSExpression()) << ",\n";
			oss << "\"expression\": " << SerializeExpression(assignmentExpr->GetExpression()) << "\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeUnaryExpression(const AST::UnaryExpression* unaryExpr)
		{
			std::ostringstream oss;
			oss << "{\"UnaryExpression\": {\n";
			oss << "\"type\": \"UnaryExpression\",\n";
			oss << "\"operator\": \"" << unaryExpr->GetOperator()->GetTypeString() << "\",\n";
			oss << "\"expression\": " << SerializeExpression(unaryExpr->GetExpression()) << "\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string StringSerializer::SerializeMemberExpression(const AST::MemberExpression* memberExpr)
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

		std::string StringSerializer::SerializeCallExpression(const AST::CallExpression* callExpr)
		{
			std::ostringstream oss;
			oss << "{\"CallExpression\": {\n";
			oss << "\"type\": \"CallExpression\",\n";
			oss << "\"callee\": " << SerializeExpression(callExpr->GetCallee()) << ",\n";
			oss << "\"arguments\": [\n";
			size_t i = 0;
			for (const auto& arg : callExpr->GetArguments())
			{
				oss << SerializeExpression(arg.get());
				i++;
				if ((i + 1) <= callExpr->GetArguments().size())
					oss << ",";
			}
			oss << "]\n";
			oss << "}\n}\n";
			return oss.str();
		}

		std::string StringSerializer::SerializePostfixExpression(const AST::PostfixExpression* postfixExpr)
		{
			std::ostringstream oss;
			oss << "{\"PostfixExpression\": {\n";
			oss << "\"type\": \"PostfixExpression\",\n";
			oss << "\"operator\": \"" << postfixExpr->GetOperator()->GetTypeString() << "\",\n";
			oss << "\"expression\": " << SerializeExpression(postfixExpr->GetExpression()) << "\n";
			oss << "}\n}";
			return oss.str();
		}
	}
}
