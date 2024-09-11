#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYETypeChecker/TypeChecker.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace TypeChecker
	{
		TEST(TypeCheckerBinaryExpressionLogicalTest, LogicalOR)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("false || true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("10 || 20;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true || 20;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"Hello\" || false;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("1 || 2.25;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("22.16 || \"Txt\";", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);
		}

		TEST(TypeCheckerBinaryExpressionLogicalTest, LogicalAND)
		{
			TypeChecker typeChecker;
			Eye::ASTGenerator::ASTGenerator astGenerator;

			auto res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("false && true;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("10 && 20;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("true && 20;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(res.has_value(), true);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("\"Hello\" && false;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("1 && 2.25;", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);

			res = typeChecker.TypeCheck(astGenerator.GenerateMemoryAST("22.16 && \"Txt\";", Eye::ASTGenerator::ASTGeneratorSourceType::String));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::TypeCheckerBadOperandType);
		}
	}
}
