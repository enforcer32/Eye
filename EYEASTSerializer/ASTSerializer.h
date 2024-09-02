#pragma once

#include <EYEAST/Program.h>

#include <string>

namespace Eye
{
	namespace ASTSerializer
	{
		class ASTSerializer
		{
		public:
			virtual std::string Serialize(const std::shared_ptr<AST::Program>& ast) = 0;
		};
	}
}
