#pragma once

#include <EYELexer/Token.h>
#include <EYEAST/Program.h>
#include <EYEAST/Statement.h>

namespace Eye
{
	namespace Parser
	{
		class Parser
		{
		public:
			bool Parse(const std::vector<Lexer::Token>& tokens);

		private:
			std::shared_ptr<AST::Program> Program();
			std::vector<std::shared_ptr<AST::Statement>> StatementList();
			std::shared_ptr<AST::Statement> Statement();

		private:
			bool HasToken() const;
			Lexer::Token NextToken();
			Lexer::Token PeekToken();

		private:
			std::shared_ptr<AST::Program> m_Program;
			std::vector<Lexer::Token> m_Tokens;
			size_t m_CurrentTokenIndex;
			Lexer::Token m_LookAhead;
		};
	}
}
