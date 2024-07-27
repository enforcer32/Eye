#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Util/FileIO.h"

#include <gtest/gtest.h>

namespace EYE
{
	TEST(CharacterTest, Character)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\Character.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		ASSERT_EQ(lexer.GetTokens()[0].Char, 't');
		ASSERT_EQ(lexer.GetTokens()[3].Char, 'A');
	}

	TEST(CharacterTest, EscapeCharacter)
	{
		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Examples\\Character.eye";
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		lexer.DebugPrintTokens();

		ASSERT_EQ(lexer.GetTokens()[7].Char, '\n');
		ASSERT_EQ(lexer.GetTokens()[8].Char, '\t');
	}
}
