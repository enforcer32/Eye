#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Util/FileIO.h"

#include <gtest/gtest.h>

namespace EYE
{
	TEST(NumberTest, Decimal)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\Number.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		ASSERT_EQ(lexer.GetTokens()[0].Number, 12345);
		ASSERT_EQ(lexer.GetTokens()[3].Number, 456);
	}

	TEST(NumberTest, Hex)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\Number2.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		ASSERT_EQ(lexer.GetTokens()[0].Number, 4660);
	}

	TEST(NumberTest, Binary)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\Number2.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		ASSERT_EQ(lexer.GetTokens()[2].Number, 6);
	}
}
