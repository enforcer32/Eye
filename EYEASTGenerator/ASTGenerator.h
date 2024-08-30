#pragma once

#include <EYEAST/Program.h>

#include <string>

namespace Eye
{
	namespace ASTGenerator
	{
		class ASTGenerator
		{
		public:
			std::shared_ptr<AST::Program> GenerateMemoryAST(const std::string& filepath);
			std::string GenerateStringAST(const std::string& filepath);
		};
	}
}
