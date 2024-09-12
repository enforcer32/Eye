#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

#define CREATE_ARITHMETIC_TEST(testOperator, testErrorType) \
	TypeChecker typeChecker; \
	Eye::ASTGenerator::ASTGenerator astGenerator; \
	\
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true" testOperator "true;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25" testOperator "true;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("false" testOperator "12.25;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"World\" " testOperator " \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"Hello\"" testOperator "123;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 " testOperator " \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 " testOperator " 512.35;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 " testOperator " 123;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25 " testOperator " 33;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25 " testOperator " 123.33;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(res.has_value(), true)

namespace Eye
{
	namespace TypeChecker
	{
		TEST(TypeCheckerBinaryExpressionArithmeticTest, ArithmeticPlus)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			//  Boolean + Boolean
			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true+true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

			// Non-Boolean + Boolean
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25+true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

			// Boolean + Non-Boolean
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("false+12.25;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

			// String + String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"World\" + \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// String + Non-String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"Hello\"+123;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// Non-String + String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 + \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// Float + Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 + 512.35;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Float + Number
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 + 123;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Number + Number
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25 + 33;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Number + Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25 + 123.33;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
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
}
