#pragma once

#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

#define CREATE_RELATIONAL_TEST(testOperator, testErrorType) \
	TypeChecker typeChecker; \
	Eye::ASTGenerator::ASTGenerator astGenerator; \
	\
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25 " testOperator " true;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("false " testOperator " 12.25;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), testErrorType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"World\" " testOperator " \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"Hello\" " testOperator " 123;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
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
		TEST(TypeCheckerBinaryExpressionRelationalTest, Equals)
		{
			CREATE_RELATIONAL_TEST("==", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true == true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);
		}

		TEST(TypeCheckerBinaryExpressionRelationalTest, NotEquals)
		{
			CREATE_RELATIONAL_TEST("!=", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true != true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);
		}

		TEST(TypeCheckerBinaryExpressionRelationalTest, Smaller)
		{
			CREATE_RELATIONAL_TEST("<", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true < true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
		}

		TEST(TypeCheckerBinaryExpressionRelationalTest, Greater)
		{
			CREATE_RELATIONAL_TEST("<", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true > true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
		}

		TEST(TypeCheckerBinaryExpressionRelationalTest, SmallerEquals)
		{
			CREATE_RELATIONAL_TEST("<", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true <= true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
		}

		TEST(TypeCheckerBinaryExpressionRelationalTest, GreaterEquals)
		{
			CREATE_RELATIONAL_TEST("<", Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true >= true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Eye::Error::ErrorType::TypeCheckerBadTypeCompare);
		}
	}
}
