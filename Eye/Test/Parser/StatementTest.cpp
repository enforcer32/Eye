#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Parser/Parser.h"
#include "Eye/Util/FileIO.h"

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>

namespace EYE
{
	TEST(ParserStatementTest, ExpressionStatement)
	{
		std::string eyeFile = "ExpressionStatement.eye";
		std::string testFile = "ExpressionStatement.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Statement\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Statement\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, BlockStatement)
	{
		std::string eyeFile = "BlockStatement.eye";
		std::string testFile = "BlockStatement.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Statement\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Statement\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, VariableStatement)
	{
		std::string eyeFile = "VariableStatement.eye";
		std::string testFile = "VariableStatement.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Statement\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Statement\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, IfStatement)
	{
		std::string eyeFile = "IfStatement.eye";
		std::string testFile = "IfStatement.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Statement\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Statement\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}
}
