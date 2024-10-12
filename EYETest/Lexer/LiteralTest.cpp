#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Utility/Logger.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(LexerLiteralTest, IntegerDecimal)
	{
		std::string testType = "Literal";
		std::string eyeFile = "IntegerDecimal.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerLiteralTest->IntegerDecimal Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetValue<IntegerType>(), 12345);
		ASSERT_EQ(tokens[2]->GetValue<IntegerType>(), 123);
		ASSERT_EQ(tokens[8]->GetValue<IntegerType>(), 214912);
	}

	TEST(LexerLiteralTest, IntegerHex)
	{
		std::string testType = "Literal";
		std::string eyeFile = "IntegerHex.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerLiteralTest->IntegerHex Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetValue<IntegerType>(), 4660);
		ASSERT_EQ(tokens[2]->GetValue<IntegerType>(), 1245);
		ASSERT_EQ(tokens[5]->GetValue<IntegerType>(), 5126788);
	}

	TEST(LexerLiteralTest, IntegerBinary)
	{
		std::string testType = "Literal";
		std::string eyeFile = "IntegerBinary.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerLiteralTest->IntegerBinary Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetValue<IntegerType>(), 6);
		ASSERT_EQ(tokens[2]->GetValue<IntegerType>(), 51256);
		ASSERT_EQ(tokens[5]->GetValue<IntegerType>(), 1256);
	}

	TEST(LexerLiteralTest, Float)
	{
		std::string testType = "Literal";
		std::string eyeFile = "Float.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerLiteralTest->Float Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetValue<FloatType>(), 123.456);
		ASSERT_EQ(tokens[2]->GetValue<FloatType>(), 12.3356);
		ASSERT_EQ(tokens[5]->GetValue<FloatType>(), 8510.1457);
	}

	TEST(LexerLiteralTest, String)
	{
		std::string testType = "Literal";
		std::string eyeFile = "String.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerLiteralTest->String Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(std::string(tokens[0]->GetValue<StringType>()), "Hello World");
		ASSERT_EQ(std::string(tokens[2]->GetValue<StringType>()), "Test\\n");
		ASSERT_EQ(std::string(tokens[5]->GetValue<StringType>()), "Bye World");
	}

	TEST(LexerLiteralTest, Boolean)
	{
		std::string testType = "Literal";
		std::string eyeFile = "Boolean.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerLiteralTest->Boolean Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetValue<BooleanType>(), true);
		ASSERT_EQ(tokens[2]->GetValue<BooleanType>(), false);
		ASSERT_EQ(tokens[2]->GetType(), TokenType::LiteralBoolean);
		ASSERT_EQ(tokens[5]->GetValue<BooleanType>(), false);
	}

	TEST(LexerLiteralTest, Null)
	{
		std::string testType = "Literal";
		std::string eyeFile = "Null.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerLiteralTest->Null Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::LiteralNull);
		ASSERT_EQ(tokens[2]->GetType(), TokenType::LiteralNull);
		ASSERT_EQ(tokens[5]->GetType(), TokenType::LiteralNull);
	}
}
