#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(TypeCheckerBinaryExpressionLogicalTest, LogicalOR)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "false || true;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "10 || 20;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true || 20;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "\"Hello\" || false;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "1 || 2.25;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "22.16 || \"Txt\";", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);
	}

	TEST(TypeCheckerBinaryExpressionLogicalTest, LogicalAND)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "false && true;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "10 && 20;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true && 20;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "\"Hello\" && false;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "1 && 2.25;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "22.16 && \"Txt\";", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);
	}
}
