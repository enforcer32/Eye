#pragma once

#include <EYEUtility/Logger.h>
#include <EYEASTGenerator/ASTGenerator.h>
#include <EYESemantic/Semantic.h>

#include <gtest/gtest.h>

namespace Eye
{
	namespace Semantic
	{
		TEST(SemanticVariableStatementTest, DeclareBeforeUse)
		{
			ASTGenerator::ASTGenerator astGenerator;
			Semantic semanticValidator;

			auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int x = 5; x = 10;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int t = 5; { t = 10; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int a = 5; { int b = 10; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "x = 5; x = 10;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int z = 5; { int y = 10; } y = 5;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int z = 5; { int y = 10; } int b = m;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);
		}

		TEST(SemanticVariableStatementTest, DeclareInSameScope)
		{
			ASTGenerator::ASTGenerator astGenerator;
			Semantic semanticValidator;

			auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int x = 5; int y = 10;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int t = 5; { int t = 10; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int a = 5; { int b = 10; { int a = 13; } }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(res.has_value(), true);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int x = 15; int x = 13;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticReDeclaration);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int z = 5; { int y = 10; int y = 13; } y = 5;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticReDeclaration);
		}

		TEST(SemanticVariableStatementTest, VoidType)
		{
			ASTGenerator::ASTGenerator astGenerator;
			Semantic semanticValidator;

			auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "void x;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticBadDataType);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "void x = 12;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticBadDataType);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int z = 5; { void y = 10; int y = 13; } y = 5;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticBadDataType);
		}

		TEST(SemanticVariableStatementTest, TypeQualifier)
		{
			ASTGenerator::ASTGenerator astGenerator;
			Semantic semanticValidator;

			auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "const int x = 12; x = 55;", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticWriteReadOnly);

			res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "const int z = 5; { const int y = 10; z = 13; }", Utility::EyeSourceType::String }, false }));
			ASSERT_EQ(!res.has_value(), true);
			ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticWriteReadOnly);
		}
	}
}
