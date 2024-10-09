#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/Utility/Logger.h"
#include "Eye/Lexer/Lexer.h"
#include "Eye/Parser/Parser.h"
#include "Eye/TypeChecker/TypeChecker.h"
#include "Eye/ASTSerializer/StringSerializer.h"

namespace Eye
{
	std::shared_ptr<AST::Program> ASTGenerator::GenerateMemoryAST(const ASTGeneratorProperties& properties)
	{
		Lexer lexer;
		auto res = lexer.Tokenize(properties.Source);
		if (!res.has_value())
		{
			EYE_LOG_ERROR(res.error().GetMessage());
			EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Lexer Failed to Tokenize!");
		}

		Parser parser;
		res = parser.Parse(std::move(res.value()));
		if (!res)
		{
			EYE_LOG_ERROR(res.error().GetMessage());
			EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Parser Failed to Parse!");
		}

		if (properties.TypeCheck)
		{
			TypeChecker typeChecker;
			res = typeChecker.TypeCheck(parser.GetAST());
			if (!res)
			{
				EYE_LOG_ERROR(res.error().GetMessage());
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST TypeChecker Failed to TypeCheck!");
			}
		}

		return parser.GetAST();
	}

	std::string ASTGenerator::GenerateStringAST(const ASTGeneratorProperties& properties)
	{
		Lexer lexer;
		auto res = lexer.Tokenize(properties.Source);
		if (!res)
		{
			EYE_LOG_ERROR(res.error().GetMessage());
			EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST Lexer Failed to Tokenize!");
		}

		Parser parser;
		res = parser.Parse(lexer.GetTokens());
		if (!res)
		{
			EYE_LOG_ERROR(res.error().GetMessage());
			EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST Parser Failed to Parse!");
		}

		if (properties.TypeCheck)
		{
			TypeChecker typeChecker;
			res = typeChecker.TypeCheck(parser.GetAST());
			if (!res)
			{
				EYE_LOG_ERROR(res.error().GetMessage());
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST TypeChecker Failed to TypeCheck!");
			}
		}

		ASTSerializer::StringSerializer astSerializer;
		std::string serialized = astSerializer.Serialize(parser.GetAST());
		if (serialized.empty())
			EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST StringSerializer Failed to Serialize!");

		return serialized;
	}
}
