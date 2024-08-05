#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Parser/Parser.h"
#include "Eye/Util/FileIO.h"

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>

namespace EYE
{
	TEST(ParserLiteralTest, Number)
	{
		std::string eyeFile = "Number.eye";
		std::string testFile = "Number.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Literal\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Literal\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserLiteralTest, String)
	{
		std::string eyeFile = "String.eye";
		std::string testFile = "String.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Literal\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Literal\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserLiteralTest, Boolean)
	{
		std::string eyeFile = "Boolean.eye";
		std::string testFile = "Boolean.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Literal\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Literal\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserLiteralTest, Null)
	{
		std::string eyeFile = "Null.eye";
		std::string testFile = "Null.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Literal\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Literal\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}
}
