#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace TypeChecker
	{
		TEST(TypeCheckerControlStatementTest, Literals)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			// Integer
			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("if(1){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("if(0){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("if(245){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("if(21.124){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("if(\"Hello\") {}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// Boolean
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("if(true){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("if(false){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);
		}

		/* IDENTIFER EXPRESSIONS
		TEST(TypeCheckerControlStatementTest, Variables)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			// Integer
			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int x = 1; if(x){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int x = 0; if(x){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("int x = 245; if(x){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			// Float
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("float x = 21.124; if(x){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// String
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("str x = \"Hello\"; if(x){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadTypeConversion);

			// Boolean
			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("bool x = true; if(x){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("bool x = false; if(x){}", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);
		}
		*/
	}
}
