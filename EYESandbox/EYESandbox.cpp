#include <EYEUtility/Logger.h>
#include <EYELexer/Lexer.h>

#include <iostream>

int main(int argc, char** argv)
{
	Eye::Logger::Init();
	EYE_LOG_INFO("EYESandbox");

	std::string testType = "Literal";
	std::string eyeFile = "Decimal.eye";
	std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

	Eye::Lexer::Lexer lexer;
	if (!lexer.Tokenize(filePath))
	{
		EYE_LOG_CRITICAL("Lexer Failed!");
		return -1;
	}

	for (const auto& tok : lexer.GetTokens())
		std::cout << tok.ToString() << std::endl;

	return 0;
}
