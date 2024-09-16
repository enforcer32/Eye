#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

#define CREATE_BITWISE_TEST(testOperator) \
	TypeChecker typeChecker; \
	Eye::ASTGenerator::ASTGenerator astGenerator; \
	 \
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "10 " testOperator " 20;", Utility::EyeSourceType::String }, false })); \
	ASSERT_EQ(res.has_value(), true); \
	 \
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "10 " testOperator " true;", Utility::EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	 \
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25.12 " testOperator " 5;", Utility::EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	 \
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "10 " testOperator " \"Hello\";", Utility::EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	 \
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true " testOperator " \"Bye\";", Utility::EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType)

namespace Eye
{
	namespace TypeChecker
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
}
