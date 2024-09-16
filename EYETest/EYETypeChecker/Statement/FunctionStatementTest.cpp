#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace TypeChecker
	{
		TEST(TypeCheckerStatementTest, FunctionStatement)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function int get(int x, float y) { return x + y; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function int get() { return 12; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function float get() { int x = 12; return x; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function str get() { return \"Hello World\"; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function str get(str t1, str t2) { return (t1 + t2); }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function bool get() { return true; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function bool get(bool state) { return state; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function int get() { return false; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function float get() { return \"Test\"; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 12; function int add(int y) { return x + y; } x = 12;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);
		}
	}
}
