#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace TypeChecker
	{
		TEST(TypeCheckerExpressionTest, CallExpression)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("function float get(int x, float y) { return x + y; } get(10, 20.25);", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("function int get(int x) { return 12; } get(25.25);", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("function float get(str text, float number) {} get(\"Hello\", 25.12);", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("function str get(bool state, int number) { } get(true, 123);", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("function str get(str t1, str t2) { return (t1 + t2); } get(12, 13);", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("function void get(int x, float y, str z, bool w) { } get(12, 22.12, \"Hello\", true);", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("function void get(int x, float y, str z, bool w) { } get(12.55, 22, false, true);", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int x = 55; float y = 35.12; str txt = \"hell\"; bool state = true; function void get(int x, float y, str z, bool w) { } get(x, y, txt, state);", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int x = 55; float y = 35.12; str txt = \"hell\"; bool state = true; function void get(int x, float y, str z, bool w) { } get(txt, y, txt, x);", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);
		}
	}
}
