#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(TypeCheckerExpressionTest, UnaryExpression)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "-1 + 5;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "1 + +5;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "!true;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "!25;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "-true + 5;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "!22.25 + 5;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "+true + 12;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "~10;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "~2.5;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "~true;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "~\"Hello\";", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

	}
}
