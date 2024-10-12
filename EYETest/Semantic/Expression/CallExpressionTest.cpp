#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/Semantic/Semantic.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(SemanticCallExpressionTest, CallBeforeDeclare)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 10; } getNumber();", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 10; } { getNumber(); }", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 10; } getNothing();", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "{ function int getNumber() { return 10; } } getNumber();", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);
	}

	TEST(SemanticCallExpressionTest, CallVariable)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 10; } getNumber();", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int getNumber = 12; getNumber();", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticCallVariable);
	}

	TEST(SemanticCallExpressionTest, CallFunctions)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int add(int x, int y) { return x; } int number1 = 12; add(number1, 15);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int add(int x, int y) { return x; } add(number, 15);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x, int y, int z, int d) { return 10; } getNumber(1, 2, 3);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticTooFewArguments);
	}

	TEST(SemanticCallExpressionTest, ArgumentCount)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 10; } getNumber();", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x) { return x; } { getNumber(123); }", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x, int y, int z, int d = 55) { return 10; } getNumber(1, 2, 3);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x, int y, int z, int d) { return 10; } getNumber(1, 2, 3);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticTooFewArguments);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x, int y) { return 10; } getNumber(1);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticTooFewArguments);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x, int y) { return 10; } getNumber(1, 2, 3);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticTooManyArguments);
	}
}
