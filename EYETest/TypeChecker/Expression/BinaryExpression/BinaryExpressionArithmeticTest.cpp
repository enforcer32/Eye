#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

#define CREATE_ARITHMETIC_TEST(testOperator, testErrorType) \
	TypeChecker typeChecker; \
	ASTGenerator astGenerator; \
	\
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true" testOperator "true;", EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25" testOperator "true;", EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "false" testOperator "12.25;", EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "\"World\" " testOperator " \"Hello\";", EyeSourceType::String }, false })); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "\"Hello\"" testOperator "123;", EyeSourceType::String }, false })); \
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
	TEST(TypeCheckerBinaryExpressionArithmeticTest, ArithmeticPlus)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		//  Boolean + Boolean
		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true+true;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		// Non-Boolean + Boolean
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25+true;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		// Boolean + Non-Boolean
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "false+12.25;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		// String + String
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "\"World\" + \"Hello\";", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		// String + Non-String
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "\"Hello\"+123;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// Non-String + String
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25.12 + \"Hello\";", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// Float + Float
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25.12 + 512.35;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		// Float + Number
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25.12 + 123;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		// Number + Number
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25 + 33;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		// Number + Float
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "25 + 123.33;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);
	}

	TEST(TypeCheckerBinaryExpressionArithmeticTest, ArithmeticMinus)
	{
		CREATE_ARITHMETIC_TEST("-", Eye::Error::ErrorType::TypeCheckerBadOperandType);
	}

	TEST(TypeCheckerBinaryExpressionArithmeticTest, ArithmeticStar)
	{
		CREATE_ARITHMETIC_TEST("*", Eye::Error::ErrorType::TypeCheckerBadOperandType);
	}

	TEST(TypeCheckerBinaryExpressionArithmeticTest, ArithmeticSlash)
	{
		CREATE_ARITHMETIC_TEST("/", Eye::Error::ErrorType::TypeCheckerBadOperandType);
	}

	TEST(TypeCheckerBinaryExpressionArithmeticTest, ArithmeticModulo)
	{
		CREATE_ARITHMETIC_TEST("%", Eye::Error::ErrorType::TypeCheckerBadOperandType);
	}
}
