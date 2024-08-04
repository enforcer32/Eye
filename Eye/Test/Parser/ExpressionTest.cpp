#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Parser/Parser.h"
#include "Eye/Util/FileIO.h"

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>

namespace EYE
{
	TEST(ExpressionTest, AdditiveBinaryExpression)
	{
		std::string eyeFile = "AdditiveBinaryExpression.eye";
		std::string testFile = "AdditiveBinaryExpression.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ExpressionTest, MultiplicativeBinaryExpression)
	{
		std::string eyeFile = "MultiplicativeBinaryExpression.eye";
		std::string testFile = "MultiplicativeBinaryExpression.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ExpressionTest, ParenthesizedExpression)
	{
		std::string eyeFile = "ParenthesizedExpression.eye";
		std::string testFile = "ParenthesizedExpression.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ExpressionTest, AssignmentExpression)
	{
		std::string eyeFile = "AssignmentExpression.eye";
		std::string testFile = "AssignmentExpression.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ExpressionTest, RelationalExpression)
	{
		std::string eyeFile = "RelationalExpression.eye";
		std::string testFile = "RelationalExpression.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ExpressionTest, EqualityExpression)
	{
		std::string eyeFile = "EqualityExpression.eye";
		std::string testFile = "EqualityExpression.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ExpressionTest, LogicalExpression)
	{
		std::string eyeFile = "LogicalExpression.eye";
		std::string testFile = "LogicalExpression.json";

		EyeInstance* eyeInstance = new EyeInstance;
		eyeInstance->InFilePath = "..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + eyeFile;
		eyeInstance->InFileStream = std::istringstream(FileIO::ReadFileContent(eyeInstance->InFilePath));

		Lexer lexer;
		lexer.Tokenize(eyeInstance);

		Parser parser;
		parser.Parse(eyeInstance);

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream("..\\..\\..\\..\\Eye\\Test\\Parser\\Expression\\" + testFile));
		nlohmann::json parserData = nlohmann::json::parse(parser.ToJSONString());
		ASSERT_EQ(testFileData, parserData);
	}
}
