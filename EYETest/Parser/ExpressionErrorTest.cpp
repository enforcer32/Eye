#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Parser/Parser.h"
#include "Eye/Utility/Logger.h"
#include "Eye/ASTSerializer/StringSerializer.h"

#include <gtest/gtest.h>

std::expected<bool, Eye::Error::Error> gRes;
#define CREATE_BINARY_ERROR_TEST(testOperator) \
	gRes = TestGenerateAST("number" testOperator "1;"); \
	ASSERT_EQ(gRes.has_value(), true); \
	\
	gRes = TestGenerateAST("10" testOperator ";"); \
	ASSERT_EQ(!gRes.has_value(), true); \
	ASSERT_EQ(gRes.error().GetType(), Error::ErrorType::ParserSyntaxError); \
	\
	gRes = TestGenerateAST(testOperator "10;"); \
	ASSERT_EQ(!gRes.has_value(), true); \
	ASSERT_EQ(gRes.error().GetType(), Error::ErrorType::ParserSyntaxError); \
	\
	gRes = TestGenerateAST(testOperator ";"); \
	ASSERT_EQ(!gRes.has_value(), true); \
	ASSERT_EQ(gRes.error().GetType(), Error::ErrorType::ParserSyntaxError)

#define CREATE_ASSIGNMENT_ERROR_TEST(testOperator) \
	gRes = TestGenerateAST("number " testOperator " 1;"); \
	ASSERT_EQ(gRes.has_value(), true); \
	 \
	gRes = TestGenerateAST(testOperator ";"); \
	ASSERT_EQ(!gRes.has_value(), true); \
	ASSERT_EQ(gRes.error().GetType(), Error::ErrorType::ParserSyntaxError); \
	 \
	gRes = TestGenerateAST(testOperator "10;"); \
	ASSERT_EQ(!gRes.has_value(), true); \
	ASSERT_EQ(gRes.error().GetType(), Error::ErrorType::ParserSyntaxError); \
	 \
	gRes = TestGenerateAST("number " testOperator ";"); \
	ASSERT_EQ(!gRes.has_value(), true); \
	ASSERT_EQ(gRes.error().GetType(), Error::ErrorType::ParserSyntaxError); \
	 \
	gRes = TestGenerateAST("num2 " testOperator ";"); \
	ASSERT_EQ(!gRes.has_value(), true); \
	ASSERT_EQ(gRes.error().GetType(), Error::ErrorType::ParserSyntaxError)

namespace Eye
{
	std::expected<bool, Error::Error> TestGenerateAST(const std::string& str)
	{
		Lexer lexer;
		auto res = lexer.Tokenize({ str, EyeSourceType::String });
		if (!res)
		{
			EYE_LOG_ERROR(res.error().GetMessage());
			EYE_LOG_CRITICAL("EYEASTGenerator->GenerateMemoryAST Lexer Failed to Tokenize!");
		}

		Parser parser;
		return parser.Parse(lexer.GetTokens());
	}

	TEST(ParserExpressionErrorTest, AssignmentExpression)
	{
		CREATE_ASSIGNMENT_ERROR_TEST("=");
		CREATE_ASSIGNMENT_ERROR_TEST("+=");
		CREATE_ASSIGNMENT_ERROR_TEST("-=");
		CREATE_ASSIGNMENT_ERROR_TEST("*=");
		CREATE_ASSIGNMENT_ERROR_TEST("/=");
		CREATE_ASSIGNMENT_ERROR_TEST("%=");
		CREATE_ASSIGNMENT_ERROR_TEST("&=");
		CREATE_ASSIGNMENT_ERROR_TEST("|=");
		CREATE_ASSIGNMENT_ERROR_TEST("^=");
		CREATE_ASSIGNMENT_ERROR_TEST(">>=");
		CREATE_ASSIGNMENT_ERROR_TEST("<<=");
	}

	TEST(ParserExpressionErrorTest, AdditiveBinaryExpression)
	{
		// +
		auto res = TestGenerateAST("number + 1;");
		ASSERT_EQ(res.has_value(), true);

		res = TestGenerateAST("10+;");
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::ParserSyntaxError);

		res = TestGenerateAST("+;");
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::ParserSyntaxError);

		// -
		res = TestGenerateAST("number - 1;");
		ASSERT_EQ(res.has_value(), true);

		res = TestGenerateAST("10-;");
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::ParserSyntaxError);

		res = TestGenerateAST("-;");
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::ParserSyntaxError);
	}

	TEST(ParserExpressionErrorTest, MultiplicativeBinaryExpression)
	{
		CREATE_BINARY_ERROR_TEST("*");
		CREATE_BINARY_ERROR_TEST("/");
		CREATE_BINARY_ERROR_TEST("%");
	}

	TEST(ParserExpressionErrorTest, BitwiseExpression)
	{
		CREATE_BINARY_ERROR_TEST("|");
		CREATE_BINARY_ERROR_TEST("&");
		CREATE_BINARY_ERROR_TEST("^");
	}

	TEST(ParserExpressionErrorTest, BitwiseShiftExpression)
	{
		CREATE_BINARY_ERROR_TEST("<<");
		CREATE_BINARY_ERROR_TEST(">>");
	}

	TEST(ParserExpressionErrorTest, RelationalExpression)
	{
		CREATE_BINARY_ERROR_TEST("<");
		CREATE_BINARY_ERROR_TEST("<=");
		CREATE_BINARY_ERROR_TEST(">");
		CREATE_BINARY_ERROR_TEST(">=");
	}

	TEST(ParserExpressionErrorTest, EqualityExpression)
	{
		CREATE_BINARY_ERROR_TEST("==");
		CREATE_BINARY_ERROR_TEST("!=");
	}

	TEST(ParserExpressionErrorTest, LogicalExpression)
	{
		CREATE_BINARY_ERROR_TEST("&&");
		CREATE_BINARY_ERROR_TEST("||");
	}
}

// 22+;
