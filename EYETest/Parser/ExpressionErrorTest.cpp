#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Parser/Parser.h"
#include "Eye/Utility/Logger.h"
#include "Eye/ASTSerializer/StringSerializer.h"

#include <gtest/gtest.h>

std::expected<std::unique_ptr<Eye::AST::Program>, Eye::Error::Error> gRes;
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
	std::expected<std::unique_ptr<AST::Program>, Error::Error> TestGenerateAST(const std::string& str)
	{
		Lexer lexer;
		auto lexerRes = lexer.Tokenize({ str, EyeSourceType::String });
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->ExpressionErrorTest->TestGenerateAST Lexer Failed to Tokenize!");
		}

		Parser parser;
		return parser.Parse(std::move(lexerRes.value()));
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

	TEST(ParserExpressionErrorTest, UnaryExpression)
	{
		auto res = TestGenerateAST("+1;");
		ASSERT_EQ(res.has_value(), true);

		res = TestGenerateAST("+;");
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::ParserSyntaxError);

		res = TestGenerateAST("-number;");
		ASSERT_EQ(res.has_value(), true);

		res = TestGenerateAST("-;");
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::ParserSyntaxError);
	}

	TEST(ParserExpressionErrorTest, PostfixPrefixExpression)
	{
		auto res = TestGenerateAST("++1;");
		ASSERT_EQ(res.has_value(), true);

		res = TestGenerateAST("++;");
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::ParserSyntaxError);

		res = TestGenerateAST("--;");
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::ParserSyntaxError);
	}
}
