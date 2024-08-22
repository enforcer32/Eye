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
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Identifier Failed to Tokenize()");

			ASSERT_EQ(std::string(lexer.GetTokens()[1].GetValue<StringType>()), "test");
			ASSERT_EQ(std::string(lexer.GetTokens()[7].GetValue<StringType>()), "num");
			ASSERT_EQ(std::string(lexer.GetTokens()[13].GetValue<StringType>()), "accurate");
			ASSERT_EQ(std::string(lexer.GetTokens()[19].GetValue<StringType>()), "text");
			ASSERT_EQ(std::string(lexer.GetTokens()[25].GetValue<StringType>()), "fake");
			ASSERT_EQ(std::string(lexer.GetTokens()[32].GetValue<StringType>()), "id");
		}

		TEST(LexerKeywordTest, Datatype)
		{
			std::string testType = "Keyword";
			std::string eyeFile = "Datatype.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Datatype Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::KeywordAuto);
			ASSERT_EQ(lexer.GetTokens()[6].GetType(), TokenType::KeywordInt);
			ASSERT_EQ(lexer.GetTokens()[12].GetType(), TokenType::KeywordFloat);
			ASSERT_EQ(lexer.GetTokens()[18].GetType(), TokenType::KeywordStr);
			ASSERT_EQ(lexer.GetTokens()[24].GetType(), TokenType::KeywordBool);
			ASSERT_EQ(lexer.GetTokens()[30].GetType(), TokenType::KeywordConst);
		}

		TEST(LexerKeywordTest, Control)
		{
			std::string testType = "Keyword";
			std::string eyeFile = "Control.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Control Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::KeywordIf);
			ASSERT_EQ(lexer.GetTokens()[9].GetType(), TokenType::KeywordElse);
		}

		TEST(LexerKeywordTest, Iteration)
		{
			std::string testType = "Keyword";
			std::string eyeFile = "Iteration.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Iteration Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::KeywordWhile);
			ASSERT_EQ(lexer.GetTokens()[7].GetType(), TokenType::KeywordBreak);
			ASSERT_EQ(lexer.GetTokens()[13].GetType(), TokenType::KeywordDo);
			ASSERT_EQ(lexer.GetTokens()[17].GetType(), TokenType::KeywordContinue);
			ASSERT_EQ(lexer.GetTokens()[28].GetType(), TokenType::KeywordFor);
		}

		TEST(LexerKeywordTest, Function)
		{
			std::string testType = "Keyword";
			std::string eyeFile = "Function.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Function Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::KeywordFunction);
			ASSERT_EQ(lexer.GetTokens()[1].GetType(), TokenType::KeywordInt);
			ASSERT_EQ(lexer.GetTokens()[2].GetType(), TokenType::Identifier);
			ASSERT_EQ(lexer.GetTokens()[4].GetType(), TokenType::KeywordInt);
			ASSERT_EQ(lexer.GetTokens()[13].GetType(), TokenType::KeywordReturn);
		}

		TEST(LexerKeywordTest, Struct)
		{
			std::string testType = "Keyword";
			std::string eyeFile = "Struct.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerKeywordTest->Struct Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::KeywordStruct);
			ASSERT_EQ(lexer.GetTokens()[1].GetType(), TokenType::Identifier);
			ASSERT_EQ(lexer.GetTokens()[20].GetType(), TokenType::KeywordNew);
		}
	}
}
