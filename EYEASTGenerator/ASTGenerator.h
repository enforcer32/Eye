#pragma once

#include <EYEUtility/EyeSource.h>
#include <EYEAST/Program.h>

namespace Eye
{
	namespace ASTGenerator
	{
		struct ASTGeneratorProperties
		{
			Utility::EyeSource Source;
			bool TypeCheck;
		};

		class ASTGenerator
		{
		public:
			std::shared_ptr<AST::Program> GenerateMemoryAST(const ASTGeneratorProperties& properties);
			std::string GenerateStringAST(const ASTGeneratorProperties& properties);
		};
	}
}
