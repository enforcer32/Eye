#include <EYEUtility/Logger.h>
#include <EYELexer/Lexer.h>
#include <EYEParser/Parser.h>
#include <EYEASTSerializer/StringSerializer.h>

#include <iostream>

int main(int argc, char** argv)
{
	Eye::Logger::Init();
	EYE_LOG_INFO("EYESandbox");

	std::string testType = "Operator";
	std::string eyeFile = "Assignment.eye";
	std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

	Eye::Lexer::Lexer lexer;
	if (!lexer.Tokenize("..\\..\\..\\..\\Examples\\Test.eye"))
	{
		EYE_LOG_CRITICAL("Lexer Failed!");
		return -1;
	}

	Eye::Parser::Parser parser;
	if (!parser.Parse(lexer.GetTokens()))
	{
		EYE_LOG_CRITICAL("Parser Failed!");
		return -1;
	}

	Eye::ASTSerializer::StringSerializer serializer;
	std::string tmpJsonStr;
	if((tmpJsonStr = serializer.Serialize(parser.GetAST())).empty())
	{
		EYE_LOG_CRITICAL("StringSerializer Failed!");
		return -1;
	}
	std::cout << tmpJsonStr << std::endl;

	return 0;
}
