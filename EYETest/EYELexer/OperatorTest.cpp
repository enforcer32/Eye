#pragma once

#include <EYELexer/Lexer.h>
#include <EYEUtility/Logger.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace Lexer
	{
		TEST(LexerOperatorTest, Arithmetic)
		{
			std::string testType = "Operator";
			std::string eyeFile = "Arithmetic.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOperatorTest->Arithmetic Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::OperatorArithmeticIncrement);
			ASSERT_EQ(lexer.GetTokens()[3].GetType(), TokenType::OperatorArithmeticDecrement);
		}

		TEST(LexerOperatorTest, Binary)
		{
			std::string testType = "Operator";
			std::string eyeFile = "Binary.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOperatorTest->Binary Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::OperatorBinaryPlus);
			ASSERT_EQ(lexer.GetTokens()[3].GetType(), TokenType::OperatorBinaryMinus);
			ASSERT_EQ(lexer.GetTokens()[6].GetType(), TokenType::OperatorBinaryStar);
			ASSERT_EQ(lexer.GetTokens()[9].GetType(), TokenType::OperatorBinarySlash);
			ASSERT_EQ(lexer.GetTokens()[12].GetType(), TokenType::OperatorBinaryModulo);
		}

		TEST(LexerOperatorTest, Assignment)
		{
			std::string testType = "Operator";
			std::string eyeFile = "Assignment.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOperatorTest->Assignment Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::OperatorAssignment);
			ASSERT_EQ(lexer.GetTokens()[3].GetType(), TokenType::OperatorAssignmentPlus);
			ASSERT_EQ(lexer.GetTokens()[6].GetType(), TokenType::OperatorAssignmentMinus);
			ASSERT_EQ(lexer.GetTokens()[9].GetType(), TokenType::OperatorAssignmentStar);
			ASSERT_EQ(lexer.GetTokens()[12].GetType(), TokenType::OperatorAssignmentSlash);
			ASSERT_EQ(lexer.GetTokens()[15].GetType(), TokenType::OperatorAssignmentModulo);
			ASSERT_EQ(lexer.GetTokens()[18].GetType(), TokenType::OperatorAssignmentBitwiseAND);
			ASSERT_EQ(lexer.GetTokens()[21].GetType(), TokenType::OperatorAssignmentBitwiseOR);
			ASSERT_EQ(lexer.GetTokens()[24].GetType(), TokenType::OperatorAssignmentBitwiseXOR);
			ASSERT_EQ(lexer.GetTokens()[27].GetType(), TokenType::OperatorAssignmentBitwiseLeftShift);
			ASSERT_EQ(lexer.GetTokens()[30].GetType(), TokenType::OperatorAssignmentBitwiseRightShift);
		}

		TEST(LexerOperatorTest, Relational)
		{
			std::string testType = "Operator";
			std::string eyeFile = "Relational.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOperatorTest->Relational Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::OperatorRelationalEquals);
			ASSERT_EQ(lexer.GetTokens()[3].GetType(), TokenType::OperatorRelationalNotEquals);
			ASSERT_EQ(lexer.GetTokens()[6].GetType(), TokenType::OperatorRelationalSmaller);
			ASSERT_EQ(lexer.GetTokens()[9].GetType(), TokenType::OperatorRelationalGreater);
			ASSERT_EQ(lexer.GetTokens()[12].GetType(), TokenType::OperatorRelationalSmallerEquals);
			ASSERT_EQ(lexer.GetTokens()[15].GetType(), TokenType::OperatorRelationalGreaterEquals);
		}

		TEST(LexerOperatorTest, Logical)
		{
			std::string testType = "Operator";
			std::string eyeFile = "Logical.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOperatorTest->Logical Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::OperatorLogicalAND);
			ASSERT_EQ(lexer.GetTokens()[3].GetType(), TokenType::OperatorLogicalOR);
			ASSERT_EQ(lexer.GetTokens()[6].GetType(), TokenType::OperatorLogicalNOT);
		}

		TEST(LexerOperatorTest, Bitwise)
		{
			std::string testType = "Operator";
			std::string eyeFile = "Bitwise.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOperatorTest->Bitwise Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::OperatorBitwiseBinaryAND);
			ASSERT_EQ(lexer.GetTokens()[3].GetType(), TokenType::OperatorBitwiseBinaryOR);
			ASSERT_EQ(lexer.GetTokens()[6].GetType(), TokenType::OperatorBitwiseBinaryXOR);
			ASSERT_EQ(lexer.GetTokens()[9].GetType(), TokenType::OperatorBitwiseLeftShift);
			ASSERT_EQ(lexer.GetTokens()[12].GetType(), TokenType::OperatorBitwiseRightShift);
			ASSERT_EQ(lexer.GetTokens()[15].GetType(), TokenType::OperatorBitwiseNOT);
		}

		TEST(LexerOperatorTest, Other)
		{
			std::string testType = "Operator";
			std::string eyeFile = "Other.eye";
			std::string filePath = "..\\..\\..\\..\\EYETest\\EYELexer\\" + testType + "\\" + eyeFile;

			Lexer lexer;
			if (!lexer.Tokenize(filePath))
				EYE_LOG_CRITICAL("EYETest->EYELexer->LexerOperatorTest->Other Failed to Tokenize()");

			ASSERT_EQ(lexer.GetTokens()[0].GetType(), TokenType::OperatorLeftParenthesis);
			ASSERT_EQ(lexer.GetTokens()[3].GetType(), TokenType::OperatorLeftBracket);
			ASSERT_EQ(lexer.GetTokens()[6].GetType(), TokenType::OperatorQuestionMark);
			ASSERT_EQ(lexer.GetTokens()[9].GetType(), TokenType::OperatorDot);
			ASSERT_EQ(lexer.GetTokens()[12].GetType(), TokenType::OperatorComma);
		}
	}
}
