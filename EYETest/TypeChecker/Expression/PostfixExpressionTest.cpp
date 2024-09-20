#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(TypeCheckerExpressionTest, PostfixExpression)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "1++ + 5;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "1 + 5--;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "22.12++;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "22.12--;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true++;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "\"hello\"++;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);
	}
}
