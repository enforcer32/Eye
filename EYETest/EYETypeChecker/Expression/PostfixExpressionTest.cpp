#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace TypeChecker
	{
		TEST(TypeCheckerExpressionTest, PostfixExpression)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "1++ + 5;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "1 + 5--;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "22.12++;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "22.12--;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "true++;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "\"hello\"++;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);
		}
	}
}
