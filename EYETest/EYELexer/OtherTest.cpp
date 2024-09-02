#pragma once

#include <EYELexer/Lexer.h>
#include <EYEUtility/Logger.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace Lexer
	{
		TEST(LexerOtherTest, SingleLineComment)
		{
			std::string testType = "Other";
			std::string eyeFile = "Comment.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOtherTest->Comment Failed to Tokenize()");

			ASSERT_EQ(std::string(lexer.GetTokens()[0]->GetValue<StringType>()), " Single Line Comment");
			ASSERT_EQ(std::string(lexer.GetTokens()[6]->GetValue<StringType>()), " 2 Second Comment");
		}

		TEST(LexerOtherTest, MultiLineComment)
		{
			std::string testType = "Other";
			std::string eyeFile = "Comment.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOtherTest->MultiLineComment Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[3]->GetType(), TokenType::Comment);
		}

		TEST(LexerOtherTest, NewLine)
		{
			std::string testType = "Other";
			std::string eyeFile = "Comment.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOtherTest->NewLine Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[1]->GetType(), TokenType::Newline);
			ASSERT_EQ(lexer.GetTokens()[2]->GetType(), TokenType::Newline);
			ASSERT_EQ(lexer.GetTokens()[4]->GetType(), TokenType::Newline);
			ASSERT_EQ(lexer.GetTokens()[5]->GetType(), TokenType::Newline);
			ASSERT_EQ(lexer.GetTokens()[7]->GetType(), TokenType::Newline);
		}

		TEST(LexerOtherTest, EndOfFile)
		{
			std::string testType = "Other";
			std::string eyeFile = "Comment.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOtherTest->EndOfFile Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[8]->GetType(), TokenType::EndOfFile);
		}
	}
}
