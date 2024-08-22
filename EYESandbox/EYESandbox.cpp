#include <EYEUtility/Logger.h>
#include <EYELexer/Lexer.h>

#include <iostream>

int main(int argc, char** argv)
{
	Eye::Logger::Init();
	EYE_LOG_INFO("EYESandbox");

	Eye::Lexer::Lexer lexer;
	if (!lexer.Tokenize("..\\..\\..\\..\\Examples\\Test.eye"))
	{
		EYE_LOG_CRITICAL("Lexer Failed!");
		return -1;
	}

	for (const auto& tok : lexer.GetTokens())
		std::cout << tok.ToString() << std::endl;

	return 0;
}
