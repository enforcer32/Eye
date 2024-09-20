#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(TypeCheckerControlStatementTest, Literals)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		// Integer
		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "if(1){}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "if(0){}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "if(245){}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		// Float
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "if(21.124){}", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// String
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "if(\"Hello\") {}", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// Boolean
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "if(true){}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "if(false){}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);
	}

	TEST(TypeCheckerControlStatementTest, Variables)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		// Integer
		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 1; if(x){}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 0; if(x){}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 245; if(x){}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		// Float
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "float x = 21.124; if(x){}", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// String
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "str x = \"Hello\"; if(x){}", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// Boolean
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool x = true; if(x){}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool x = false; if(x){}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);
	}
}
