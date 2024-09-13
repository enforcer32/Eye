#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

#define CREATE_ARITHMETIC_ASSIGNMENT_TEST(testOperator) \
	TypeChecker typeChecker; \
	Eye::ASTGenerator::ASTGenerator astGenerator; \
	\
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int x = 12; x " testOperator " 14;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int x = 12; x " testOperator " 22.15;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 12; x " testOperator " 14;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 12; x " testOperator " 11.15;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 14.24; x " testOperator " \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("bool x = true; x " testOperator " 14;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 12; x " testOperator " false;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("str test = \"Hello\"; test " testOperator " \"bye\";", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("str test = \"Hello\"; test " testOperator " 22;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType)

#define CREATE_BITWISE_ASSIGMENT_TEST(testOperator) \
	TypeChecker typeChecker; \
	Eye::ASTGenerator::ASTGenerator astGenerator; \
	\
	auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int number = 10; number &= 20;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(res.has_value(), true); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int number = 10; number &= true;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float number = 25.12; number &= 10;", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int number = 10; number &= \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType); \
	\
	res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("bool state = true; state &= \"Bye\";", Eye::ASTGenerator::ASTGeneratorSourceType::String)); \
	ASSERT_EQ(!res.has_value(), true); \
	ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType)

namespace Eye
{
	namespace TypeChecker
	{
		TEST(TypeCheckerAssignmentExpressionTest, Assignment)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 14.24; int y; y = x;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 14.24; float x2; x2 = x; float x3; x3 = x2; str tmp; tmp = x3;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("bool state; { state = false; { bool state2; { state2 = state; } } }", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int x; x = 55; int x2; x2 = x; int x3; x3 = x2;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);
		}

		TEST(TypeCheckerAssignmentExpressionTest, AssignmentPlus)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int x = 12; x += 14;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int x = 12; x += 22.15;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 12; x += 14;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 12; x += 11.15;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 14.24; x += \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("bool x = true; x += 14;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 12; x += false;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("str test = \"Hello\"; test += \"bye\";", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("str test = \"Hello\"; test += 22;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);
		}

		TEST(TypeCheckerAssignmentExpressionTest, AssignmentMinus)
		{
			CREATE_ARITHMETIC_ASSIGNMENT_TEST("-=");
		}

		TEST(TypeCheckerAssignmentExpressionTest, AssignmentStar)
		{
			CREATE_ARITHMETIC_ASSIGNMENT_TEST("*=");
		}

		TEST(TypeCheckerAssignmentExpressionTest, AssignmentSlash)
		{
			CREATE_ARITHMETIC_ASSIGNMENT_TEST("/=");
		}

		TEST(TypeCheckerAssignmentExpressionTest, AssignmentModulo)
		{
			CREATE_ARITHMETIC_ASSIGNMENT_TEST("%=");
		}

		TEST(TypeCheckerAssignmentExpressionTest, AssignmentBitwiseAND)
		{
			CREATE_BITWISE_ASSIGMENT_TEST("&=");
		}

		TEST(TypeCheckerAssignmentExpressionTest, AssignmentBitwiseOR)
		{
			CREATE_BITWISE_ASSIGMENT_TEST("|=");
		}

		TEST(TypeCheckerAssignmentExpressionTest, AssignmentBitwiseXOR)
		{
			CREATE_BITWISE_ASSIGMENT_TEST("^=");
		}

		TEST(TypeCheckerAssignmentExpressionTest, AssignmentBitwiseLeftShift)
		{
			CREATE_BITWISE_ASSIGMENT_TEST("<<");
		}

		TEST(TypeCheckerAssignmentExpressionTest, AssignmentBitwiseRightShift)
		{
			CREATE_BITWISE_ASSIGMENT_TEST(">>");
		}
	}
}
