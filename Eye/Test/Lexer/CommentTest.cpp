#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Util/FileIO.h"

#include <gtest/gtest.h>

namespace EYE
{
	TEST(CommentTest, SingeLineComment)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\Comment.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		ASSERT_EQ(std::string{ lexer.GetTokens()[0].String }, " Single Line Comment");
		ASSERT_EQ(std::string{ lexer.GetTokens()[6].String }, " 2 Second Comment");
	}

	TEST(CommentTest, MultiLineComment)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\Comment.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		ASSERT_EQ(lexer.GetTokens()[3].Type, TokenType::Comment);
	}
}
