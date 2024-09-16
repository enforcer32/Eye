#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace TypeChecker
	{
		TEST(TypeCheckerIterationStatementTest, WhileStatement)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			// Integer
			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(1){}", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(0){}", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(245){ int x = 12.24; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(21.124){}", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(\"Hello\") {}", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// Boolean
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "while(true){ (25 != true); }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeCompare);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 2; while(x){}", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);
		}

		TEST(TypeCheckerIterationStatementTest, DoWhileStatement)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			// Integer
			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do {str x = \"h\";} while(1);", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do { float test = true; } while(0);", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do {} while(245);", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			// Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do {} while(21.124);", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do {} while(\"Hello\");", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// Boolean
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "do { (true < 12); } while(true);", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeCompare);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "int x = 1; do {} while(x);", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);
		}

		TEST(TypeCheckerIterationStatementTest, ForStatement)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			// Integer
			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(int x = 12; x < 5; x+1) {str x = \"h\";}", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(;;) { float test = true; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(int x = 12; ;);", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			// Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(int x = 12; x < 21.124; x+1) {}", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			// String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(float y = \"Hello\"; ;);", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// Boolean
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(bool nothing = false; nothing != true;) bool nothing2 = true;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "for(; true; );", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST({ { "bool nothing; for(nothing = true; nothing != true;) nothing = true;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);
		}
	}
}
