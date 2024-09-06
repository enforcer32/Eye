#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace TypeChecker
	{
		TEST(TypeCheckerBinaryExpressionRelationalTest, RelationalEqual)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			//  Boolean == Boolean
			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true == true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Non-Boolean == Boolean
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25 == true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeCompare);

			// Boolean == Non-Boolean
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("false == 12.25;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeCompare);

			// String == String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"World\" == \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// String == Non-String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"Hello\" == 123;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeCompare);

			// Non-String == String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 == \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeCompare);

			// Float == Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 == 512.35;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Float == Number
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 == 123;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Number == Number
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25 == 33;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Number == Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25 == 123.33;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);
		}
	}
}
