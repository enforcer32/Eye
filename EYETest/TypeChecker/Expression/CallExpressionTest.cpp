#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(TypeCheckerExpressionTest, CallExpression)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function float get(int x, float y) { return x + y; } get(10, 20.25);", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function int get(int x) { return 12; } get(25.25);", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function float get(str text, float number) {} get(\"Hello\", 25.12);", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function str get(bool state, int number) { } get(true, 123);", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function str get(str t1, str t2) { return (t1 + t2); } get(12, 13);", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function void get(int x, float y, str z, bool w) { } get(12, 22.12, \"Hello\", true);", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function void get(int x, float y, str z, bool w) { } get(12.55, 22, false, true);", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 55; float y = 35.12; str txt = \"hell\"; bool state = true; function void get(int x, float y, str z, bool w) { } get(x, y, txt, state);", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 55; float y = 35.12; str txt = \"hell\"; bool state = true; function void get(int x, float y, str z, bool w) { } get(txt, y, txt, x);", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "function int add(int x, int y) { return add(x, y); } add(10, 20);", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);
	}
}
