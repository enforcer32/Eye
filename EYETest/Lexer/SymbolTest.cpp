#pragma once

#include "Eye/Lexer/Lexer.h"
#include "Eye/Utility/Logger.h"

#include <gtest/gtest.h>

namespace Eye
{
	TEST(LexerSymbolTest, Regular)
	{
		std::string testType = "Symbol";
		std::string eyeFile = "Regular.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerSymbolTest->Regular Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::SymbolRightParenthesis);
		ASSERT_EQ(tokens[2]->GetType(), TokenType::SymbolRightBracket);
		ASSERT_EQ(tokens[4]->GetType(), TokenType::SymbolLeftBrace);
		ASSERT_EQ(tokens[6]->GetType(), TokenType::SymbolRightBrace);
		ASSERT_EQ(tokens[8]->GetType(), TokenType::SymbolColon);
		ASSERT_EQ(tokens[10]->GetType(), TokenType::SymbolSemiColon);
		ASSERT_EQ(tokens[12]->GetType(), TokenType::SymbolBackslash);
	}

	TEST(LexerSymbolTest, MathExpr)
	{
		std::string testType = "Symbol";
		std::string eyeFile = "MathExpr.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Eye::Lexer lexer;
		auto lexerRes = lexer.Tokenize(EyeSource(filePath, EyeSourceType::File));
		if (!lexerRes.has_value())
		{
			EYE_LOG_ERROR(lexerRes.error().GetMessage());
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerSymbolTest->MathExpr Failed to Tokenize()");
		}
		auto tokens = lexerRes.value();

		ASSERT_EQ(tokens[0]->GetType(), TokenType::SymbolLeftBrace);
		ASSERT_EQ(tokens[6]->GetType(), TokenType::SymbolRightParenthesis);
		ASSERT_EQ(tokens[7]->GetType(), TokenType::SymbolSemiColon);
		ASSERT_EQ(tokens[9]->GetType(), TokenType::OperatorLeftBracket);
		ASSERT_EQ(tokens[10]->GetType(), TokenType::SymbolColon);
		ASSERT_EQ(tokens[11]->GetType(), TokenType::SymbolRightBracket);
		ASSERT_EQ(tokens[14]->GetType(), TokenType::SymbolRightBrace);
	}
}
