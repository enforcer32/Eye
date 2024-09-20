#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(TypeCheckerVariableStatementTest, Literals)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		// Integer
		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 12;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 25.13; ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = \"hello\"; ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = true; ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// Float
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "float x = 22.13;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "float x = 145;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "float x = \"hello\"; ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "float x = true; ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// String
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "str x = \"hello\"; ", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "str x = 145;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "str x = 22.13;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "str x = true; ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// Boolean
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool x = true; ", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool x = 145;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool x = 22.13;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool x = \"hello\"; ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);
	}

	TEST(TypeCheckerVariableStatementTest, Expression)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		// Integer
		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = (10 + 25.13);", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = (10 + 14);", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		// Float
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "float x = (10 + 25.13);", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "float x = (12.15 + true);", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		// String
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "str x = (\"hello\" + 22); ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "str x = (\"hello\" + \"bye\"); ", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		// Boolean
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool x = (true + 1); ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool x = (true + false); ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);
	}
}
