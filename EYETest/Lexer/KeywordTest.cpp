#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Utility/Logger.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(LexerKeywordTest, Identifier)
	{
		std::string testType = "Keyword";
		std::string eyeFile = "Datatype.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerKeywordTest->Identifier Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(std::string(tokens[1]->GetValue<StringType>()), "test");
		ASSERT_EQ(std::string(tokens[7]->GetValue<StringType>()), "num");
		ASSERT_EQ(std::string(tokens[13]->GetValue<StringType>()), "accurate");
		ASSERT_EQ(std::string(tokens[19]->GetValue<StringType>()), "text");
		ASSERT_EQ(std::string(tokens[25]->GetValue<StringType>()), "fake");
		ASSERT_EQ(std::string(tokens[32]->GetValue<StringType>()), "id");
	}

	TEST(LexerKeywordTest, Datatype)
	{
		std::string testType = "Keyword";
		std::string eyeFile = "Datatype.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerKeywordTest->Datatype Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::KeywordDataTypeInt);
		ASSERT_EQ(tokens[6]->GetType(), TokenType::KeywordDataTypeInt);
		ASSERT_EQ(tokens[12]->GetType(), TokenType::KeywordDataTypeFloat);
		ASSERT_EQ(tokens[18]->GetType(), TokenType::KeywordDataTypeStr);
		ASSERT_EQ(tokens[24]->GetType(), TokenType::KeywordDataTypeBool);
		ASSERT_EQ(tokens[30]->GetType(), TokenType::KeywordTypeQualifierConst);
		ASSERT_EQ(tokens[37]->GetType(), TokenType::KeywordDataTypeVoid);
	}

	TEST(LexerKeywordTest, Control)
	{
		std::string testType = "Keyword";
		std::string eyeFile = "Control.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerKeywordTest->Control Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::KeywordControlIf);
		ASSERT_EQ(tokens[9]->GetType(), TokenType::KeywordControlElse);
	}

	TEST(LexerKeywordTest, Iteration)
	{
		std::string testType = "Keyword";
		std::string eyeFile = "Iteration.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerKeywordTest->Iteration Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::KeywordIterationWhile);
		ASSERT_EQ(tokens[7]->GetType(), TokenType::KeywordIterationBreak);
		ASSERT_EQ(tokens[13]->GetType(), TokenType::KeywordIterationDo);
		ASSERT_EQ(tokens[17]->GetType(), TokenType::KeywordIterationContinue);
		ASSERT_EQ(tokens[28]->GetType(), TokenType::KeywordIterationFor);
	}

	TEST(LexerKeywordTest, Function)
	{
		std::string testType = "Keyword";
		std::string eyeFile = "Function.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerKeywordTest->Function Failed to Tokenize()");
		}
		const auto& tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::KeywordFunction);
		ASSERT_EQ(tokens[1]->GetType(), TokenType::KeywordDataTypeInt);
		ASSERT_EQ(tokens[2]->GetType(), TokenType::Identifier);
		ASSERT_EQ(tokens[4]->GetType(), TokenType::KeywordDataTypeInt);
		ASSERT_EQ(tokens[13]->GetType(), TokenType::KeywordReturn);
	}
}
