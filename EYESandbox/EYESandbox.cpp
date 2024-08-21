#include <EYEUtility/Logger.h>
#include <EYELexer/Token.h>

#include <iostream>

int main(int argc, char** argv)
{
	Eye::Logger::Init();
	EYE_LOG_INFO("EYESandbox");

	Eye::Lexer::Token token("test", {});
	Eye::Lexer::Token token2(Eye::Lexer::TokenType::KeywordAuto, {});
	Eye::Lexer::Token token3(123.456, {});
	Eye::Lexer::Token token4((Eye::Lexer::Integer)789, {});
	Eye::Lexer::Token token5(Eye::Lexer::TokenType::OperatorAssignmentBitwiseAND, {});

	std::cout << token.ToString() << std::endl;
	std::cout << token2.ToString() << std::endl;
	std::cout << token3.ToString() << std::endl;
	std::cout << token4.ToString() << std::endl;
	std::cout << token5.ToString() << std::endl;

	return 0;
}
