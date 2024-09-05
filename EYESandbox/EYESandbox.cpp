#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <EYELexer/Lexer.h>
//#include <EYEParser/Parser.h>

#include <iostream>
#include <chrono>

int main(int argc, char** argv)
{
	Eye::Logger::Init();
	EYE_LOG_INFO("EYESandbox");

	Eye::Lexer::Lexer lexer;
	auto res = lexer.Tokenize("..\\..\\..\\..\\Examples\\Test.eye");
	if (!res)
	{
		EYE_LOG_ERROR(res.error().GetMessage());
		EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST Lexer Failed to Tokenize!");
	}

	/*Eye::Parser::Parser parser;
	res = parser.Parse(lexer.GetTokens());
	if (!res)
	{
		EYE_LOG_ERROR(res.error().GetMessage());
		EYE_LOG_CRITICAL("EYEASTGenerator->GenerateStringAST Parser Failed to Parse!");
	}*/

	/*
	Eye::ASTGenerator::ASTGenerator astGenerator;
	auto start = std::chrono::high_resolution_clock::now();
	astGenerator.GenerateStringAST("..\\..\\..\\..\\Examples\\Test.eye");
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Duration: " << duration << std::endl; // Before->Optimization 5972ms, After->Optimization 2667ms, (copy paste Examples/Test.eye until 111240 lines of code)
	*/


	//Eye::ASTGenerator::ASTGenerator astGenerator;
	//astGenerator.GenerateStringAST("..\\..\\..\\..\\Examples\\Test.eye");

	/*Eye::TypeChecker::TypeChecker typeChecker;
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("..\\..\\..\\..\\Examples\\Test.eye"));
	if (!res)
	{
		EYE_LOG_ERROR(res.error().GetMessage());
		EYE_LOG_CRITICAL("EYETypeChecker Failed");
	}*/

	return 0;
}
