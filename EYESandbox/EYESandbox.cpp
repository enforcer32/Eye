#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>

#include <iostream>

int main(int argc, char** argv)
{
	Eye::Logger::Init();
	EYE_LOG_INFO("EYESandbox");

	Eye::ASTGenerator::ASTGenerator astGenerator;
	std::cout << astGenerator.GenerateStringAST("..\\..\\..\\..\\Examples\\Test.eye") << std::endl;

	return 0;
}
