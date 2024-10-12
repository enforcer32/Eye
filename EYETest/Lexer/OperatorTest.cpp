#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Utility/Logger.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(LexerOperatorTest, Arithmetic)
	{
		std::string testType = "Operator";
		std::string eyeFile = "Arithmetic.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOperatorTest->Arithmetic Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::OperatorArithmeticIncrement);
		ASSERT_EQ(tokens[3]->GetType(), TokenType::OperatorArithmeticDecrement);
	}

	TEST(LexerOperatorTest, Binary)
	{
		std::string testType = "Operator";
		std::string eyeFile = "Binary.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOperatorTest->Binary Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::OperatorBinaryPlus);
		ASSERT_EQ(tokens[3]->GetType(), TokenType::OperatorBinaryMinus);
		ASSERT_EQ(tokens[6]->GetType(), TokenType::OperatorBinaryStar);
		ASSERT_EQ(tokens[9]->GetType(), TokenType::OperatorBinarySlash);
		ASSERT_EQ(tokens[12]->GetType(), TokenType::OperatorBinaryModulo);
	}

	TEST(LexerOperatorTest, Assignment)
	{
		std::string testType = "Operator";
		std::string eyeFile = "Assignment.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOperatorTest->Assignment Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::OperatorAssignment);
		ASSERT_EQ(tokens[3]->GetType(), TokenType::OperatorAssignmentPlus);
		ASSERT_EQ(tokens[6]->GetType(), TokenType::OperatorAssignmentMinus);
		ASSERT_EQ(tokens[9]->GetType(), TokenType::OperatorAssignmentStar);
		ASSERT_EQ(tokens[12]->GetType(), TokenType::OperatorAssignmentSlash);
		ASSERT_EQ(tokens[15]->GetType(), TokenType::OperatorAssignmentModulo);
		ASSERT_EQ(tokens[18]->GetType(), TokenType::OperatorAssignmentBitwiseAND);
		ASSERT_EQ(tokens[21]->GetType(), TokenType::OperatorAssignmentBitwiseOR);
		ASSERT_EQ(tokens[24]->GetType(), TokenType::OperatorAssignmentBitwiseXOR);
		ASSERT_EQ(tokens[27]->GetType(), TokenType::OperatorAssignmentBitwiseLeftShift);
		ASSERT_EQ(tokens[30]->GetType(), TokenType::OperatorAssignmentBitwiseRightShift);
	}

	TEST(LexerOperatorTest, Relational)
	{
		std::string testType = "Operator";
		std::string eyeFile = "Relational.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOperatorTest->Relational Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::OperatorRelationalEquals);
		ASSERT_EQ(tokens[3]->GetType(), TokenType::OperatorRelationalNotEquals);
		ASSERT_EQ(tokens[6]->GetType(), TokenType::OperatorRelationalSmaller);
		ASSERT_EQ(tokens[9]->GetType(), TokenType::OperatorRelationalGreater);
		ASSERT_EQ(tokens[12]->GetType(), TokenType::OperatorRelationalSmallerEquals);
		ASSERT_EQ(tokens[15]->GetType(), TokenType::OperatorRelationalGreaterEquals);
	}

	TEST(LexerOperatorTest, Logical)
	{
		std::string testType = "Operator";
		std::string eyeFile = "Logical.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOperatorTest->Logical Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::OperatorLogicalAND);
		ASSERT_EQ(tokens[3]->GetType(), TokenType::OperatorLogicalOR);
		ASSERT_EQ(tokens[6]->GetType(), TokenType::OperatorLogicalNOT);
	}

	TEST(LexerOperatorTest, Bitwise)
	{
		std::string testType = "Operator";
		std::string eyeFile = "Bitwise.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOperatorTest->Bitwise Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::OperatorBitwiseBinaryAND);
		ASSERT_EQ(tokens[3]->GetType(), TokenType::OperatorBitwiseBinaryOR);
		ASSERT_EQ(tokens[6]->GetType(), TokenType::OperatorBitwiseBinaryXOR);
		ASSERT_EQ(tokens[9]->GetType(), TokenType::OperatorBitwiseLeftShift);
		ASSERT_EQ(tokens[12]->GetType(), TokenType::OperatorBitwiseRightShift);
		ASSERT_EQ(tokens[15]->GetType(), TokenType::OperatorBitwiseNOT);
	}

	TEST(LexerOperatorTest, Other)
	{
		std::string testType = "Operator";
		std::string eyeFile = "Other.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOperatorTest->Other Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::OperatorLeftParenthesis);
		ASSERT_EQ(tokens[3]->GetType(), TokenType::OperatorLeftBracket);
		ASSERT_EQ(tokens[6]->GetType(), TokenType::OperatorQuestionMark);
		ASSERT_EQ(tokens[9]->GetType(), TokenType::OperatorDot);
		ASSERT_EQ(tokens[12]->GetType(), TokenType::OperatorComma);
	}

	TEST(LexerOperatorTest, Chained)
	{
		std::string testType = "Operator";
		std::string eyeFile = "Chained.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerOperatorTest->Chained Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::OperatorAssignmentBitwiseLeftShift);
		ASSERT_EQ(tokens[1]->GetType(), TokenType::OperatorArithmeticIncrement);
		ASSERT_EQ(tokens[2]->GetType(), TokenType::OperatorBinaryPlus);
		ASSERT_EQ(tokens[3]->GetType(), TokenType::OperatorBinaryMinus);
		ASSERT_EQ(tokens[4]->GetType(), TokenType::OperatorBinaryPlus);
		ASSERT_EQ(tokens[5]->GetType(), TokenType::OperatorRelationalSmaller);
		ASSERT_EQ(tokens[6]->GetType(), TokenType::OperatorBinaryPlus);
	}
}
