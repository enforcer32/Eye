#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Util/FileIO.h"

#include <gtest/gtest.h>

namespace EYE
{
	TEST(LexerSymbolTest, Symbol)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\Symbol.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		ASSERT_EQ(lexer.GetTokens()[0].Char, ':');
		ASSERT_EQ(lexer.GetTokens()[2].Char, ')');
	}
}
