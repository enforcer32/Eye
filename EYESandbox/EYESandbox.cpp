#include <Eye/Utility/Logger.h>
#include <Eye/ASTGenerator/ASTGenerator.h>
#include <Eye/Semantic/Semantic.h>

#include <Eye/Lexer/Lexer.h>
#include <Eye/Parser/Parser.h>
#include <Eye/ASTSerializer/StringSerializer.h>

#include <iostream>
#include <chrono>

int main(int argc, char** argv)
{
	Eye::Logger::Init();
	EYE_LOG_INFO("EYESandbox");

	/*
	Eye::ASTGenerator astGenerator;
	auto start = std::chrono::high_resolution_clock::now();
	astGenerator.GenerateStringAST("..\\..\\..\\..\\Examples\\Test.eye");
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Duration: " << duration << std::endl; // Before->Optimization 5972ms, After->Optimization 2667ms, (copy paste Examples/Test.eye until 111240 lines of code)
	*/

	/*
	Eye::ASTGenerator astGenerator;
	//std::cout << astGenerator.GenerateStringAST({ { "..\\..\\..\\..\\Examples\\Test.eye", Eye::EyeSourceType::File }, false }) << std::endl;

	Eye::Semantic semanticValidator;
	auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "..\\..\\..\\..\\Examples\\Test.eye", Eye::EyeSourceType::File }, false }));
	if (!res)
	{
		EYE_LOG_ERROR(res.error().GetMessage());
		EYE_LOG_CRITICAL("EYESemantic->Validate Failed!");
	}
	*/

	Eye::EyeSource source("..\\..\\..\\..\\Examples\\Test.eye", Eye::EyeSourceType::File);
	Eye::Lexer lexer;
	auto res = lexer.Tokenize(source);
	if (!res)
	{
		EYE_LOG_ERROR(res.error().GetMessage());
		EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Lexer Failed to Tokenize!");
	}

	Eye::Parser parser;
	res = parser.Parse(lexer.GetTokens());
	if (!res)
	{
		EYE_LOG_ERROR(res.error().GetMessage());
		EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Parser Failed to Parse!");
	}

	Eye::ASTSerializer::StringSerializer serialize;
	std::cout << serialize.Serialize(parser.GetAST()) << std::endl;

	return 0;
}
