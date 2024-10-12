#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

#define CREATE_BITWISE_TEST(testOperator) \
	TypeChecker typeChecker; \
	ASTGenerator astGenerator; \
	 \
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "10 " testOperator " 20;", EyeSourceType::String }, false, false }).get()); \
	ASSERT_EQ(res.has_value(), true); \
	 \
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "10 " testOperator " true;", EyeSourceType::String }, false, false }).get()); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	 \
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25.12 " testOperator " 5;", EyeSourceType::String }, false, false }).get()); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	 \
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "10 " testOperator " \"Hello\";", EyeSourceType::String }, false, false }).get()); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	 \
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true " testOperator " \"Bye\";", EyeSourceType::String }, false, false }).get()); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType)

namespace Eye
{
	TEST(TypeCheckerBinaryExpressionBitwiseTest, BitwiseAND)
	{
		CREATE_BITWISE_TEST("&");
	}

	TEST(TypeCheckerBinaryExpressionBitwiseTest, BitwiseOR)
	{
		CREATE_BITWISE_TEST("|");
	}

	TEST(TypeCheckerBinaryExpressionBitwiseTest, BitwiseXOR)
	{
		CREATE_BITWISE_TEST("^");
	}

	TEST(TypeCheckerBinaryExpressionBitwiseTest, BitwiseLeftShit)
	{
		CREATE_BITWISE_TEST("<<");
	}

	TEST(TypeCheckerBinaryExpressionBitwiseTest, BitwiseRightShift)
	{
		CREATE_BITWISE_TEST(">>");
	}
}
