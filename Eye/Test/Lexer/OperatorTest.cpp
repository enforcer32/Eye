#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Util/FileIO.h"

#include <gtest/gtest.h>

namespace EYE
{
	TEST(OperatorTest, Operator)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\Operator.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		ASSERT_EQ(std::string{ lexer.GetTokens()[0].String }, "++");
		ASSERT_EQ(std::string{ lexer.GetTokens()[3].String }, "+=");
	}
}
