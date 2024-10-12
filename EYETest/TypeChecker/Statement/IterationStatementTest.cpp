#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/TypeChecker/TypeChecker.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(TypeCheckerIterationStatementTest, WhileStatement)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		// Integer
		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(1){}", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(0){}", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(245){ int x = 12.24; }", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// Float
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(21.124){}", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// String
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(\"Hello\") {}", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// Boolean
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(true){ (25 != true); }", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeCompare);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 2; while(x){}", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);
	}

	TEST(TypeCheckerIterationStatementTest, DoWhileStatement)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		// Integer
		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do {str x = \"h\";} while(1);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do { float test = true; } while(0);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do {} while(245);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		// Float
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do {} while(21.124);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// String
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do {} while(\"Hello\");", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// Boolean
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do { (true < 12); } while(true);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeCompare);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 1; do {} while(x);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);
	}

	TEST(TypeCheckerIterationStatementTest, ForStatement)
	{
		TypeChecker typeChecker;
		ASTGenerator astGenerator;

		// Integer
		auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(int x = 12; x < 5; x+1) {str x = \"h\";}", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(;;) { float test = true; }", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(int x = 12; ;);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		// Float
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(int x = 12; x < 21.124; x+1) {}", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		// String
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(float y = \"Hello\"; ;);", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

		// Boolean
		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(bool nothing = false; nothing != true;) bool nothing2 = true;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(; true; );", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);

		res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool nothing; for(nothing = true; nothing != true;) nothing = true;", EyeSourceType::String }, false, false }).get());
		ASSERT_EQ(res.has_value(), true);
	}
}
