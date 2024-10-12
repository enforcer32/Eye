#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Parser/Parser.h"
#include "Eye/Utility/Logger.h"
#include "Eye/ASTSerializer/StringSerializer.h"

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>

namespace Eye
{
	TEST(ParserStatementTest, ExpressionStatement)
	{
		std::string testType = "Statement";
		std::string eyeFile = "ExpressionStatement.eye";
		std::string testFile = "ExpressionStatement.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->ExpressionStatement Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->ExpressionStatement Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, BlockStatement)
	{
		std::string testType = "Statement";
		std::string eyeFile = "BlockStatement.eye";
		std::string testFile = "BlockStatement.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->BlockStatement Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->BlockStatement Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, VariableStatement)
	{
		std::string testType = "Statement";
		std::string eyeFile = "VariableStatement.eye";
		std::string testFile = "VariableStatement.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->VariableStatement Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->VariableStatement Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, ControlStatement)
	{
		std::string testType = "Statement";
		std::string eyeFile = "ControlStatement.eye";
		std::string testFile = "ControlStatement.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->ControlStatement Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->ControlStatement Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, IterationWhileStatement)
	{
		std::string testType = "Statement";
		std::string eyeFile = "IterationWhileStatement.eye";
		std::string testFile = "IterationWhileStatement.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->IterationWhileStatement Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->IterationWhileStatement Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, IterationDoWhileStatement)
	{
		std::string testType = "Statement";
		std::string eyeFile = "IterationDoWhileStatement.eye";
		std::string testFile = "IterationDoWhileStatement.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->IterationDoWhileStatement Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->IterationDoWhileStatement Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, IterationForStatement)
	{
		std::string testType = "Statement";
		std::string eyeFile = "IterationForStatement.eye";
		std::string testFile = "IterationForStatement.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->IterationForStatement Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->IterationForStatement Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, FunctionReturnStatement)
	{
		std::string testType = "Statement";
		std::string eyeFile = "FunctionReturnStatement.eye";
		std::string testFile = "FunctionReturnStatement.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->FunctionReturnStatement Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->FunctionReturnStatement Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, TypeQualifierStatement)
	{
		std::string testType = "Statement";
		std::string eyeFile = "TypeQualifierStatement.eye";
		std::string testFile = "TypeQualifierStatement.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->TypeQualifierStatement Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->TypeQualifierStatement Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserStatementTest, ContinueBreakStatement)
	{
		std::string testType = "Statement";
		std::string eyeFile = "ContinueBreakStatement.eye";
		std::string testFile = "ContinueBreakStatement.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->ContinueBreakStatement Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserStatementTest->ContinueBreakStatement Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}
}
