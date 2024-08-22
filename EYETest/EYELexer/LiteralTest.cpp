#pragma once

#include <EYELexer/Lexer.h>
#include <EYEUtility/Logger.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace Lexer
	{
		TEST(LexerLiteralTest, IntegerDecimal)
		{
			std::string testType = "Literal";
			std::string eyeFile = "IntegerDecimal.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerLiteralTest->IntegerDecimal Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetValue<Integer>(), 12345);
			ASSERT_EQ(lexer.GetTokens()[2].GetValue<Integer>(), 123);
			ASSERT_EQ(lexer.GetTokens()[8].GetValue<Integer>(), 214912);
		}

		TEST(LexerLiteralTest, IntegerHex)
		{
			std::string testType = "Literal";
			std::string eyeFile = "IntegerHex.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerLiteralTest->IntegerHex Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetValue<Integer>(), 4660);
			ASSERT_EQ(lexer.GetTokens()[2].GetValue<Integer>(), 1245);
			ASSERT_EQ(lexer.GetTokens()[5].GetValue<Integer>(), 5126788);
		}

		TEST(LexerLiteralTest, IntegerBinary)
		{
			std::string testType = "Literal";
			std::string eyeFile = "IntegerBinary.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerLiteralTest->IntegerBinary Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetValue<Integer>(), 6);
			ASSERT_EQ(lexer.GetTokens()[2].GetValue<Integer>(), 51256);
			ASSERT_EQ(lexer.GetTokens()[5].GetValue<Integer>(), 1256);
		}
	}
}
