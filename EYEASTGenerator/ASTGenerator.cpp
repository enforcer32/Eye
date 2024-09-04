#include "EYEASTGenerator/ASTGenerator.h"

#include <EYELexer/Lexer.h>
#include <EYEParser/Parser.h>
#include <EYEUtility/Logger.h>
#include <EYEASTSerializer/StringSerializer.h>

namespace Eye
{
	namespace ASTGenerator
	{
		std::shared_ptr<AST::Program> ASTGenerator::GenerateMemoryAST(const std::string& filepath)
		{
			Lexer::Lexer lexer;
			if (!lexer.Tokenize(filepath))
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Lexer Failed to Tokenize!");

			Parser::Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Parser Failed to Parse!");

			return parser.GetAST();
		}

		std::string ASTGenerator::GenerateStringAST(const std::string& filepath)
		{
			Lexer::Lexer lexer;

			auto res = lexer.Tokenize(filepath);
			if (!res)
			{
				EYE_LOG_ERROR(res.error().GetMessage());
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST Lexer Failed to Tokenize!");
			}

			Parser::Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST Parser Failed to Parse!");

			ASTSerializer::StringSerializer astSerializer;
			std::string serialized = astSerializer.Serialize(parser.GetAST());
			if (serialized.empty())
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST StringSerializer Failed to Serialize!");

			return serialized;
		}
	}
}
