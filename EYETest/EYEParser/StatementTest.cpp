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
		TEST(ParserStatementTest, ExpressionStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "ExpressionStatement.eye";
			std::string testFile = "ExpressionStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->ExpressionStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->ExpressionStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;
			
			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, BlockStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "BlockStatement.eye";
			std::string testFile = "BlockStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->BlockStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->BlockStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, VariableStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "VariableStatement.eye";
			std::string testFile = "VariableStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->VariableStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->VariableStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, ControlStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "ControlStatement.eye";
			std::string testFile = "ControlStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->ControlStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->ControlStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, IterationStatementWhile)
		{
			std::string testType = "Statement";
			std::string eyeFile = "IterationStatementWhile.eye";
			std::string testFile = "IterationStatementWhile.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->IterationStatementWhile Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->IterationStatementWhile Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, IterationStatementDoWhile)
		{
			std::string testType = "Statement";
			std::string eyeFile = "IterationStatementDoWhile.eye";
			std::string testFile = "IterationStatementDoWhile.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->IterationStatementDoWhile Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->IterationStatementDoWhile Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}
	}
}
