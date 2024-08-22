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

			ASSERT_EQ(lexer.GetTokens()[0].GetValue<IntegerType>(), 12345);
			ASSERT_EQ(lexer.GetTokens()[2].GetValue<IntegerType>(), 123);
			ASSERT_EQ(lexer.GetTokens()[8].GetValue<IntegerType>(), 214912);
		}

		TEST(LexerLiteralTest, IntegerHex)
		{
			std::string testType = "Literal";
			std::string eyeFile = "IntegerHex.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerLiteralTest->IntegerHex Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetValue<IntegerType>(), 4660);
			ASSERT_EQ(lexer.GetTokens()[2].GetValue<IntegerType>(), 1245);
			ASSERT_EQ(lexer.GetTokens()[5].GetValue<IntegerType>(), 5126788);
		}

		TEST(LexerLiteralTest, IntegerBinary)
		{
			std::string testType = "Literal";
			std::string eyeFile = "IntegerBinary.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerLiteralTest->IntegerBinary Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetValue<IntegerType>(), 6);
			ASSERT_EQ(lexer.GetTokens()[2].GetValue<IntegerType>(), 51256);
			ASSERT_EQ(lexer.GetTokens()[5].GetValue<IntegerType>(), 1256);
		}

		TEST(LexerLiteralTest, Float)
		{
			std::string testType = "Literal";
			std::string eyeFile = "Float.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerLiteralTest->Float Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetValue<FloatType>(), 123.456);
			ASSERT_EQ(lexer.GetTokens()[2].GetValue<FloatType>(), 12.3356);
			ASSERT_EQ(lexer.GetTokens()[5].GetValue<FloatType>(), 8510.1457);
		}

		TEST(LexerLiteralTest, String)
		{
			std::string testType = "Literal";
			std::string eyeFile = "String.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerLiteralTest->String Failed to Tokenize()");

			ASSERT_EQ(std::string(lexer.GetTokens()[0].GetValue<StringType>()), "Hello World");
			ASSERT_EQ(std::string(lexer.GetTokens()[2].GetValue<StringType>()), "Test\\n");
			ASSERT_EQ(std::string(lexer.GetTokens()[5].GetValue<StringType>()), "Bye World");
		}

		TEST(LexerLiteralTest, Boolean)
		{
			std::string testType = "Literal";
			std::string eyeFile = "Boolean.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerLiteralTest->Boolean Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetValue<BooleanType>(), true);
			ASSERT_EQ(lexer.GetTokens()[2].GetValue<BooleanType>(), false);
			ASSERT_EQ(lexer.GetTokens()[2].GetType(), TokenType::LiteralBoolean);
			ASSERT_EQ(lexer.GetTokens()[5].GetValue<BooleanType>(), false);
		}

		TEST(LexerLiteralTest, Null)
		{
			std::string testType = "Literal";
			std::string eyeFile = "Null.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerLiteralTest->Null Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::LiteralNull);
			ASSERT_EQ(lexer.GetTokens()[2].GetType(), TokenType::LiteralNull);
			ASSERT_EQ(lexer.GetTokens()[5].GetType(), TokenType::LiteralNull);
		}
	}
}
