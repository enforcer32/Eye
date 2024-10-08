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

		Lexer lexer;
		if (!lexer.Tokenize(EyeSource(filePath, EyeSourceType::File)))
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerSymbolTest->Function Failed to Tokenize()");

		ASSERT_EQ(lexer.GetTokens()[0]->GetType(), TokenType::SymbolRightParenthesis);
		ASSERT_EQ(lexer.GetTokens()[2]->GetType(), TokenType::SymbolRightBracket);
		ASSERT_EQ(lexer.GetTokens()[4]->GetType(), TokenType::SymbolLeftBrace);
		ASSERT_EQ(lexer.GetTokens()[6]->GetType(), TokenType::SymbolRightBrace);
		ASSERT_EQ(lexer.GetTokens()[8]->GetType(), TokenType::SymbolColon);
		ASSERT_EQ(lexer.GetTokens()[10]->GetType(), TokenType::SymbolSemiColon);
		ASSERT_EQ(lexer.GetTokens()[12]->GetType(), TokenType::SymbolBackslash);
	}

	TEST(LexerSymbolTest, MathExpr)
	{
		std::string testType = "Symbol";
		std::string eyeFile = "MathExpr.eye";
		std::string filePath = "..\\..\\..\\..\\EyeTest\\Lexer\\" + testType + "\\" + eyeFile;

		Lexer lexer;
		if (!lexer.Tokenize(EyeSource(filePath, EyeSourceType::File)))
			EYE_LOG_CRITICAL("EyeTest->Lexer->LexerSymbolTest->Function Failed to Tokenize()");

		ASSERT_EQ(lexer.GetTokens()[0]->GetType(), TokenType::SymbolLeftBrace);
		ASSERT_EQ(lexer.GetTokens()[6]->GetType(), TokenType::SymbolRightParenthesis);
		ASSERT_EQ(lexer.GetTokens()[7]->GetType(), TokenType::SymbolSemiColon);
		ASSERT_EQ(lexer.GetTokens()[9]->GetType(), TokenType::OperatorLeftBracket);
		ASSERT_EQ(lexer.GetTokens()[10]->GetType(), TokenType::SymbolColon);
		ASSERT_EQ(lexer.GetTokens()[11]->GetType(), TokenType::SymbolRightBracket);
		ASSERT_EQ(lexer.GetTokens()[14]->GetType(), TokenType::SymbolRightBrace);
	}
}
