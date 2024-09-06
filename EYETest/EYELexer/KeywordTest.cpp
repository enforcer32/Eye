#pragma once

#include <EYELexer/Lexer.h>
#include <EYEUtility/Logger.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace Lexer
	{
		TEST(LexerKeywordTest, Identifier)
		{
			std::string testType = "Keyword";
			std::string eyeFile = "Datatype.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(filePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Identifier Failed to Tokenize()");

			ASSERT_EQ(std::string(lexer.GetTokens()[1]->GetValue<StringType>()), "test");
			ASSERT_EQ(std::string(lexer.GetTokens()[7]->GetValue<StringType>()), "num");
			ASSERT_EQ(std::string(lexer.GetTokens()[13]->GetValue<StringType>()), "accurate");
			ASSERT_EQ(std::string(lexer.GetTokens()[19]->GetValue<StringType>()), "text");
			ASSERT_EQ(std::string(lexer.GetTokens()[25]->GetValue<StringType>()), "fake");
			ASSERT_EQ(std::string(lexer.GetTokens()[32]->GetValue<StringType>()), "id");
		}

		TEST(LexerKeywordTest, Datatype)
		{
			std::string testType = "Keyword";
			std::string eyeFile = "Datatype.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(filePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Datatype Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0]->GetType(), TokenType::KeywordDataTypeInt);
			ASSERT_EQ(lexer.GetTokens()[6]->GetType(), TokenType::KeywordDataTypeInt);
			ASSERT_EQ(lexer.GetTokens()[12]->GetType(), TokenType::KeywordDataTypeFloat);
			ASSERT_EQ(lexer.GetTokens()[18]->GetType(), TokenType::KeywordDataTypeStr);
			ASSERT_EQ(lexer.GetTokens()[24]->GetType(), TokenType::KeywordDataTypeBool);
			ASSERT_EQ(lexer.GetTokens()[30]->GetType(), TokenType::KeywordTypeQualifierConst);
			ASSERT_EQ(lexer.GetTokens()[37]->GetType(), TokenType::KeywordDataTypeVoid);
		}

		TEST(LexerKeywordTest, Control)
		{
			std::string testType = "Keyword";
			std::string eyeFile = "Control.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(filePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Control Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0]->GetType(), TokenType::KeywordControlIf);
			ASSERT_EQ(lexer.GetTokens()[9]->GetType(), TokenType::KeywordControlElse);
		}

		TEST(LexerKeywordTest, Iteration)
		{
			std::string testType = "Keyword";
			std::string eyeFile = "Iteration.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(filePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Iteration Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0]->GetType(), TokenType::KeywordIterationWhile);
			ASSERT_EQ(lexer.GetTokens()[7]->GetType(), TokenType::KeywordIterationBreak);
			ASSERT_EQ(lexer.GetTokens()[13]->GetType(), TokenType::KeywordIterationDo);
			ASSERT_EQ(lexer.GetTokens()[17]->GetType(), TokenType::KeywordIterationContinue);
			ASSERT_EQ(lexer.GetTokens()[28]->GetType(), TokenType::KeywordIterationFor);
		}

		TEST(LexerKeywordTest, Function)
		{
			std::string testType = "Keyword";
			std::string eyeFile = "Function.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(Utility::EyeSource(filePath, Utility::EyeSourceType::File)))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Function Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0]->GetType(), TokenType::KeywordFunction);
			ASSERT_EQ(lexer.GetTokens()[1]->GetType(), TokenType::KeywordDataTypeInt);
			ASSERT_EQ(lexer.GetTokens()[2]->GetType(), TokenType::Identifier);
			ASSERT_EQ(lexer.GetTokens()[4]->GetType(), TokenType::KeywordDataTypeInt);
			ASSERT_EQ(lexer.GetTokens()[13]->GetType(), TokenType::KeywordReturn);
		}
	}
}
