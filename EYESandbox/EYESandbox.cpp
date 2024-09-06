#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <iostream>
#include <chrono>

int main(int argc, char** argv)
{
	Eye::Logger::Init();
	EYE_LOG_INFO("EYESandbox");

	/*
	Eye::ASTGenerator::ASTGenerator astGenerator;
	auto start = std::chrono::high_resolution_clock::now();
	astGenerator.GenerateStringAST("..\\..\\..\\..\\Examples\\Test.eye");
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Duration: " << duration << std::endl; // Before->Optimization 5972ms, After->Optimization 2667ms, (copy paste Examples/Test.eye until 111240 lines of code)
	*/

	Eye::ASTGenerator::ASTGenerator astGenerator;
	//std::cout << astGenerator.GenerateStringAST("..\\..\\..\\..\\Examples\\Test.eye") << std::endl;

	/*Eye::TypeChecker::TypeChecker typeChecker;
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("..\\..\\..\\..\\Examples\\Test.eye", Eye::ASTGenerator::ASTGeneratorSourceType::File));
	if (!res)
	{
		EYE_LOG_ERROR(res.error().GetMessage());
		EYE_LOG_CRITICAL("EYETypeChecker Failed");
	}*/

	Eye::TypeChecker::TypeChecker typeChecker;
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("1+true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
	if (!res)
	{
		EYE_LOG_ERROR(res.error().GetMessage());
		EYE_LOG_CRITICAL("EYETypeChecker Failed");
	}

	return 0;
}
