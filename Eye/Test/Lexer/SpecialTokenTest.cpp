#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Util/FileIO.h"

#include <gtest/gtest.h>

namespace EYE
{
	TEST(LexerSpecialTokenTest, Identifier)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\SpecialToken.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		ASSERT_EQ(std::string(lexer.GetTokens()[0].String), "myName123");
		ASSERT_EQ(std::string(lexer.GetTokens()[3].String), "word");
		ASSERT_EQ(std::string(lexer.GetTokens()[4].String), "_IdentifierHere");
	}

	TEST(LexerSpecialTokenTest, Keyword)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\SpecialToken.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		ASSERT_EQ(std::string(lexer.GetTokens()[1].String), "const");
		ASSERT_EQ(std::string(lexer.GetTokens()[7].String), "function");
	}
}
