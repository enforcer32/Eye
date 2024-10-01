#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/Semantic/Semantic.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(SemanticVariableStatementTest, UseBeforeDeclare)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int x = 5; x = 10;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int t = 5; { t = 10; }", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int a = 5; { int b = 10; }", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "x = 5; x = 10;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int z = 5; { int y = 10; } y = 5;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int z = 5; { int y = 10; } int b = m;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);
	}

	TEST(SemanticVariableStatementTest, ReDeclareInSameScope)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int x = 5; int y = 10;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int t = 5; { int t = 10; }", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int a = 5; { int b = 10; { int a = 13; } }", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int x = 15; int x = 13;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticReDeclaration);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int z = 5; { int y = 10; int y = 13; } y = 5;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticReDeclaration);
	}

	TEST(SemanticVariableStatementTest, VoidType)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "void x;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticBadDataType);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "void x = 12;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticBadDataType);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int z = 5; { void y = 10; int y = 13; } y = 5;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticBadDataType);
	}

	TEST(SemanticVariableStatementTest, TypeQualifier)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "const int x = 12; x = 55;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticWriteReadOnly);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "const int z = 5; { const int y = 10; z = 13; }", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticWriteReadOnly);
	}
}
