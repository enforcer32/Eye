#pragma once

#include "Eye/Utility/Logger.h"
#include "Eye/ASTGenerator/ASTGenerator.h"
#include "Eye/Semantic/Semantic.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(SemanticCallExpressionTest, CallBeforeDeclare)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 10; } getNumber();", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 10; } { getNumber(); }", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 10; } getNothing();", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "{ function int getNumber() { return 10; } } getNumber();", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticNotDeclared);
	}

	TEST(SemanticCallExpressionTest, CallVariable)
	{
		ASTGenerator astGenerator;
		Semantic semanticValidator;

		auto res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "function int getNumber() { return 10; } getNumber();", EyeSourceType::String }, false }));
		ASSERT_EQ(res.has_value(), true);

		res = semanticValidator.Validate(astGenerator.GenerateMemoryAST({ { "int getNumber = 12; getNumber();", EyeSourceType::String }, false }));
		ASSERT_EQ(!res.has_value(), true);
		ASSERT_EQ(res.error().GetType(), Error::ErrorType::SemanticCallVariable);
	}
}
