#pragma once

#include "Eye/AST/Program.h"

#include <string>

namespace Eye
{
	namespace ASTSerializer
	{
		class ASTSerializer
		{
		public:
			virtual std::string Serialize(const AST::Program* ast) = 0;
		};
	}
}
