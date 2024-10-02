#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/Semantic/Semantic.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(SemanticFunctionStatementTest, ReDeclareInSameScope)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function void getNothing() {} int y = 10;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function void getNothing() {} function void getNothing2() {}", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function void getNothing() {} function void getNothing() {}", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticReDeclaration);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int getNothing = 12; function void getNothing() {}", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticReDeclaration);
	}

	TEST(SemanticFunctionStatementTest, ReturnFromVoid)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function void getNothing() {} int y = 10;", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function void getNothing() { return 12; } int y = 10;", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticReturnFromVoid);
	}

	TEST(SemanticFunctionStatementTest, NonVoidReturn)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function void getNothing() {} ", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function float getNumber() { float x = 22; return x; }", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNothing() { } ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNoReturn);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function str getName() { return \"Hello\"; } ", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function str getName() { } ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNoReturn);
	}

	TEST(SemanticFunctionStatementTest, MultipleReturnScope)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 20; } ", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		//res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { int x = 12; if(x == 10) return 5; else return 30; }", EyeSourceType::String }, false }));
		//ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 20; return 30; } ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticMultipleReturn);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 20; { return 30; } } ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticMultipleReturn);
	}

	TEST(SemanticFunctionStatementTest, DefaultParameterValue)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x, int y = 10) { return 20; } ", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x = 5, int y = 10, int z = 22) { return 20; } ", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x, int y = 10, int z = 22) { return 20; } ", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x = 10, int y, int z) { return 20; } ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticMissingArgument);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber(int x, int y = 20, int z) { return 20; } ", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticMissingArgument);
	}
}
