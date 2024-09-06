#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace TypeChecker
	{
		TEST(TypeCheckerBinaryExpressionTest, BinaryExpressionArithmeticPlus)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			//  Boolean + Boolean
			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true+true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// X + Boolean || Boolean + X
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25+true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// String + Non-String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"Hello\"+123;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// Non-String + String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 + \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// String + String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"World\" + \"Hello\";", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Float + Number
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25.12 + 123;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Number + Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("25 + 123.33;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);
		}
	}
}
