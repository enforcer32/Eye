#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(TypeCheckerStatementTest, BlockStatement)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 1; { int y = 12; }", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "float x = 14.25; { int y = x; }", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "str x = \"h\"; { { float y = x; } } ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool state = true; { bool state2 = state; { bool state3 = state2; } }", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);
	}
}
