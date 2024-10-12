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
	TEST(ParserExpressionTest, LiteralExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "LiteralExpression.eye";
		std::string testFile = "LiteralExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->LiteralExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->LiteralExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, AdditiveBinaryExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "AdditiveBinaryExpression.eye";
		std::string testFile = "AdditiveBinaryExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->AdditiveBinaryExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->AdditiveBinaryExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, MultiplicativeBinaryExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "MultiplicativeBinaryExpression.eye";
		std::string testFile = "MultiplicativeBinaryExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->MultiplicativeBinaryExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->MultiplicativeBinaryExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, BitwiseExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "BitwiseExpression.eye";
		std::string testFile = "BitwiseExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->BitwiseExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->BitwiseExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, BitwiseShiftExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "BitwiseShiftExpression.eye";
		std::string testFile = "BitwiseShiftExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->BitwiseShiftExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->BitwiseShiftExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, IdentifierExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "IdentifierExpression.eye";
		std::string testFile = "IdentifierExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->IdentifierExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->IdentifierExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, AssignmentExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "AssignmentExpression.eye";
		std::string testFile = "AssignmentExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->AssignmentExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->AssignmentExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, RelationalExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "RelationalExpression.eye";
		std::string testFile = "RelationalExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->RelationalExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->RelationalExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, EqualityExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "EqualityExpression.eye";
		std::string testFile = "EqualityExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->EqualityExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->EqualityExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, LogicalExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "LogicalExpression.eye";
		std::string testFile = "LogicalExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->LogicalExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->LogicalExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, UnaryExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "UnaryExpression.eye";
		std::string testFile = "UnaryExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->UnaryExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->UnaryExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, ParenthesizedExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "ParenthesizedExpression.eye";
		std::string testFile = "ParenthesizedExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->ParenthesizedExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->ParenthesizedExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, MemberExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "MemberExpression.eye";
		std::string testFile = "MemberExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->MemberExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->MemberExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, CallExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "CallExpression.eye";
		std::string testFile = "CallExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->CallExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->CallExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}

	TEST(ParserExpressionTest, PostfixPrefixExpression)
	{
		std::string testType = "Expression";
		std::string eyeFile = "PostfixPrefixExpression.eye";
		std::string testFile = "PostfixPrefixExpression.json";
		std::string eyeFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + eyeFile;
		std::string testFilePath = "..\\..\\..\\..\\EyeTest\\Parser\\" + testType + "\\" + testFile;

		Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(eyeFilePath, EyeSourceType::File));
		if (!lexerRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->PostfixPrefixExpression Failed to Tokenize()");

		Parser parser;
		auto parserRes = parser.Parse(std::move(lexerRes.value()));
		if (!parserRes.has_value())
			EYE_LOG_CRITICAL("EyeTest->Parser->ParserExpressionTest->PostfixPrefixExpression Failed to Parse()");

		ASTSerializer::StringSerializer astSerializer;

		nlohmann::json testFileData = nlohmann::json::parse(std::ifstream(testFilePath));
		nlohmann::json parserData = nlohmann::json::parse(astSerializer.Serialize(parserRes.value().get()));
		ASSERT_EQ(testFileData, parserData);
	}
}
