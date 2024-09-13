#include "EYEASTGenerator/ASTGenerator.h"

#include <EYELexer/Lexer.h>
#include <EYEParser/Parser.h>
#include <EYEUtility/Logger.h>
#include <EYEASTSerializer/StringSerializer.h>
#include <EYETypeChecker/TypeChecker.h>

namespace Eye
{
	namespace ASTGenerator
	{
		std::shared_ptr<AST::Program> ASTGenerator::GenerateMemoryAST(const std::string& source, ASTGeneratorSourceType sourceType, bool typeChecked)
		{
			Utility::EyeSource eyeSource;
			eyeSource.Source = source;
			eyeSource.Type = (sourceType == ASTGeneratorSourceType::File ? Utility::EyeSourceType::File : Utility::EyeSourceType::String);

			Lexer::Lexer lexer;
			auto res = lexer.Tokenize(eyeSource);
			if (!res)
			{
				EYE_LOG_ERROR(res.error().GetMessage());
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Lexer Failed to Tokenize!");
			}

			Parser::Parser parser;
			res = parser.Parse(lexer.GetTokens());
			if (!res)
			{
				EYE_LOG_ERROR(res.error().GetMessage());
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Parser Failed to Parse!");
			}

			if (typeChecked)
			{
				TypeChecker::TypeChecker typeChecker;
				res = typeChecker.TypeCheck(parser.GetAST());
				if (!res)
				{
					EYE_LOG_ERROR(res.error().GetMessage());
					EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST TypeChecker Failed to TypeCheck!");
				}
			}
			
			return parser.GetAST();
		}

		std::string ASTGenerator::GenerateStringAST(const std::string& source, ASTGeneratorSourceType sourceType, bool typeChecked)
		{
			Utility::EyeSource eyeSource;
			eyeSource.Source = source;
			eyeSource.Type = (sourceType == ASTGeneratorSourceType::File ? Utility::EyeSourceType::File : Utility::EyeSourceType::String);

			Lexer::Lexer lexer;
			auto res = lexer.Tokenize(eyeSource);
			if (!res)
			{
				EYE_LOG_ERROR(res.error().GetMessage());
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST Lexer Failed to Tokenize!");
			}

			Parser::Parser parser;
			res = parser.Parse(lexer.GetTokens());
			if (!res)
			{
				EYE_LOG_ERROR(res.error().GetMessage());
				EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST Parser Failed to Parse!");
			}

			if (typeChecked)
			{
				TypeChecker::TypeChecker typeChecker;
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
}
