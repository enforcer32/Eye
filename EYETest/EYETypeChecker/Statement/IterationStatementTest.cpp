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
			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("while(1){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("while(0){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("while(245){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("while(21.124){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("while(\"Hello\") {}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// Boolean
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("while(true){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("while(false){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);
		}
	}
}
