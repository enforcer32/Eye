#pragma once

#include <EYEAST/Program.h>

#include <string>

namespace Eye
{
	namespace ASTGenerator
	{
		enum ASTGeneratorSourceType
		{
			File,
			String,
		};

		class ASTGenerator
		{
		public:
			std::shared_ptr<AST::Program> GenerateMemoryAST(const std::string& source, ASTGeneratorSourceType sourceType, bool typeChecked = false);
			std::string GenerateStringAST(const std::string& source, ASTGeneratorSourceType sourceType, bool typeChecked = false);
		};
	}
}
