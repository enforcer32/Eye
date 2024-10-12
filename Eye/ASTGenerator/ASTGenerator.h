#pragma once

#include "Eye/Utility/EyeSource.h"
#include "Eye/AST/Program.h"

namespace Eye
{
	struct ASTGeneratorProperties
	{
		EyeSource Source;
		bool TypeCheck = true;
		bool ValidateSemantics = true;
	};

	class ASTGenerator
	{
	public:
		std::unique_ptr<AST::Program> GenerateMemoryAST(const ASTGeneratorProperties& properties);
		std::string GenerateStringAST(const ASTGeneratorProperties& properties);
	};
}
