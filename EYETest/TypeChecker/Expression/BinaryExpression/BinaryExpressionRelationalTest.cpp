#pragma once

#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

#define CREATE_RELATIONAL_TEST(testOperator, testErrorType) \
	TypeChecker typeChecker; \
	ASTGenerator astGenerator; \
	\
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25 " testOperator " true;", EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "false " testOperator " 12.25;", EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "\"World\" " testOperator " \"Hello\";", EyeSourceType::String }, false })); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "\"Hello\" " testOperator " 123;", EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25.12 " testOperator " \"Hello\";", EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25.12 " testOperator " 512.35;", EyeSourceType::String }, false })); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25.12 " testOperator " 123;", EyeSourceType::String }, false })); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25 " testOperator " 33;", EyeSourceType::String }, false })); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25 " testOperator " 123.33;", EyeSourceType::String }, false })); \
	ASSERT_EQ(res.has_value(), true)

namespace Eye
{
	TEST(TypeCheckerBinaryExpressionRelationalTest, Equals)
	{
		CREATE_RELATIONAL_TEST("==", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true == true;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);
	}

	TEST(TypeCheckerBinaryExpressionRelationalTest, NotEquals)
	{
		CREATE_RELATIONAL_TEST("!=", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true != true;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);
	}

	TEST(TypeCheckerBinaryExpressionRelationalTest, Smaller)
	{
		CREATE_RELATIONAL_TEST("<", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true < true;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
	}

	TEST(TypeCheckerBinaryExpressionRelationalTest, Greater)
	{
		CREATE_RELATIONAL_TEST("<", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true > true;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
	}

	TEST(TypeCheckerBinaryExpressionRelationalTest, SmallerEquals)
	{
		CREATE_RELATIONAL_TEST("<", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true <= true;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
	}

	TEST(TypeCheckerBinaryExpressionRelationalTest, GreaterEquals)
	{
		CREATE_RELATIONAL_TEST("<", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true >= true;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
	}
}
