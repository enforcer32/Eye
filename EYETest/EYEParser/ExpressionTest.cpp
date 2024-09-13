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
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
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
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
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
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->MultiplicativeBinaryExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->MultiplicativeBinaryExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, BitwiseExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "BitwiseExpression.eye";
			std::string testFile = "BitwiseExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->BitwiseExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->BitwiseExpression Failed to Parse()");

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
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
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
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
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
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
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
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->EqualityExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->EqualityExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, LogicalExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "LogicalExpression.eye";
			std::string testFile = "LogicalExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->LogicalExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->LogicalExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, UnaryExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "UnaryExpression.eye";
			std::string testFile = "UnaryExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->UnaryExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->UnaryExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, ParenthesizedExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "ParenthesizedExpression.eye";
			std::string testFile = "ParenthesizedExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->ParenthesizedExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->ParenthesizedExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, MemberExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "MemberExpression.eye";
			std::string testFile = "MemberExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->MemberExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->MemberExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, CallExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "CallExpression.eye";
			std::string testFile = "CallExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->CallExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->CallExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}

		TEST(ParserExpressionTest, PostfixPrefixExpression)
		{
			std::string testType = "Expression";
			std::string eyeFile = "PostfixPrefixExpression.eye";
			std::string testFile = "PostfixPrefixExpression.json";
			std::string eyeFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + eyeFile;
			std::string testFilePath = "..\\..\\..\\..\\EYETest\\EYEParser\\" + testType + "\\" + testFile;

			Lexer::Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(eyeFilePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->PostfixPrefixExpression Failed to Tokenize()");

			Parser parser;
			if (!parser.Parse(lexer.GetTokens()))
				EYE_LOG_CRITICAL("EYETest->EYEParser->ParserExpressionTest->PostfixPrefixExpression Failed to Parse()");

			ASTSerializer::StringSerializer astSerializer;

			nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
			nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parser.GetAST()));
			ASSERT_EQ(testFileData, parserData);
		}
	}
}
