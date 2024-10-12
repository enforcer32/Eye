#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/Utility/Logger.h"
#include "Eye/Lexer/Lexer.h"
#include "Eye/Parser/Parser.h"
#include "Eye/Semantic/Semantic.h"
#include "Eye/TypeChecker/TypeChecker.h"
#include "Eye/ASTSerializer/StringSerializer.h"

namespace Eye
{
	std::unique_ptr<AST::Program> ASTGenerator::GenerateMemoryAST(const ASTGeneratorProperties& properties)
	{
		Lexer lexer;
		auto lexerRes = lexer.Tokenize(properties.Source);
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Lexer Failed to Tokenize!");
		}

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
		{
			EYE_LOG_ERROR(parserRes.error().GetMessage());
			EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Parser Failed to Parse!");
		}

		if (properties.ValidateSemantics)
		{
			Eye::Semantic semanticValidator;
			auto semanticRes = semanticValidator.Validate(parserRes.value().get());
			if (!semanticRes)
			{
				EYE_LOG_ERROR(semanticRes.error().GetMessage());
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Semantic Failed to Validate!");
			}
		}

		if (properties.TypeCheck)
		{
			TypeChecker typeChecker;
			auto typeCheckerRes = typeChecker.TypeCheck(parserRes.value().get());
			if (!typeCheckerRes.has_value())
			{
				EYE_LOG_ERROR(typeCheckerRes.error().GetMessage());
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST TypeChecker Failed to TypeCheck!");
			}
		}

		return std::move(parserRes.value());
	}

	std::string ASTGenerator::GenerateStringAST(const ASTGeneratorProperties& properties)
	{
		ASTSerializer::StringSerializer astSerializer;
		std::string serialized = astSerializer.Serialize(GenerateMemoryAST(properties).get());
		if (serialized.empty())
			EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST StringSerializer Failed to Serialize!");

		return serialized;
	}
}
