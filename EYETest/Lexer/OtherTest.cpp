#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Utility/Logger.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(LexerOtherTest, SingleLineComment)
	{
		std::string testType = "Other";
		std::string eyeFile = "Comment.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOtherTest->Comment Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(std::string(tokens[0]->GetValue<StringType>()), " Single Line Comment");
		ASSERT_EQ(std::string(tokens[6]->GetValue<StringType>()), " 2 Second Comment");
	}

	TEST(LexerOtherTest, MultiLineComment)
	{
		std::string testType = "Other";
		std::string eyeFile = "Comment.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOtherTest->MultiLineComment Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[3]->GetType(), TokenType::Comment);
	}

	TEST(LexerOtherTest, NewLine)
	{
		std::string testType = "Other";
		std::string eyeFile = "Comment.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOtherTest->NewLine Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[1]->GetType(), TokenType::Newline);
		ASSERT_EQ(tokens[2]->GetType(), TokenType::Newline);
		ASSERT_EQ(tokens[4]->GetType(), TokenType::Newline);
		ASSERT_EQ(tokens[5]->GetType(), TokenType::Newline);
		ASSERT_EQ(tokens[7]->GetType(), TokenType::Newline);
	}

	TEST(LexerOtherTest, EndOfFile)
	{
		std::string testType = "Other";
		std::string eyeFile = "Comment.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOtherTest->EndOfFile Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[8]->GetType(), TokenType::EndOfFile);
	}
}
