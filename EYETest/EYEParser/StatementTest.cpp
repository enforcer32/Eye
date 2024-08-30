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

		TEST(ParserStatementTest, IterationWhileStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "IterationWhileStatement.eye";
			std::string testFile = "IterationWhileStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->IterationWhileStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->IterationWhileStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, IterationDoWhileStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "IterationDoWhileStatement.eye";
			std::string testFile = "IterationDoWhileStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->IterationDoWhileStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->IterationDoWhileStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, IterationForStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "IterationForStatement.eye";
			std::string testFile = "IterationForStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->IterationForStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->IterationForStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, FunctionReturnStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "FunctionReturnStatement.eye";
			std::string testFile = "FunctionReturnStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->FunctionReturnStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->FunctionReturnStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, StructStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "StructStatement.eye";
			std::string testFile = "StructStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->StructStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->StructStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, TypeQualifierStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "TypeQualifierStatement.eye";
			std::string testFile = "TypeQualifierStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->TypeQualifierStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->TypeQualifierStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserStatementTest, ContinueBreakStatement)
		{
			std::string testType = "Statement";
			std::string eyeFile = "ContinueBreakStatement.eye";
			std::string testFile = "ContinueBreakStatement.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(eyeFilePath))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->ContinueBreakStatement Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserStatementTest->ContinueBreakStatement Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}
	}
}
