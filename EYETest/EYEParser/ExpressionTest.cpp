#pragma once

#include <EYELexer/Lexer.h>
#include <EYEParser/Parser.h>
#include <EYEUtility/Logger.h>
#include <EYEASTSerializer/StringSerializer.h>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>

namespace Eye
{
	namespace Parser
	{
		TEST(ParserExpressionTest, LiteralExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "LiteralExpression.eye";
			std::string testFile = "LiteralExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->LiteralExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->LiteralExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, AdditiveBinaryExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "AdditiveBinaryExpression.eye";
			std::string testFile = "AdditiveBinaryExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->AdditiveBinaryExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->AdditiveBinaryExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, MultiplicativeBinaryExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "MultiplicativeBinaryExpression.eye";
			std::string testFile = "MultiplicativeBinaryExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->MultiplicativeBinaryExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->MultiplicativeBinaryExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, IdentifierExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "IdentifierExpression.eye";
			std::string testFile = "IdentifierExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->IdentifierExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->IdentifierExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, AssignmentExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "AssignmentExpression.eye";
			std::string testFile = "AssignmentExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->AssignmentExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->AssignmentExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, RelationalExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "RelationalExpression.eye";
			std::string testFile = "RelationalExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->RelationalExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->RelationalExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, EqualityExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "EqualityExpression.eye";
			std::string testFile = "EqualityExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->EqualityExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->EqualityExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}
	}
}
