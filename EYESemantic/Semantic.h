#pragma once

#include <EYEError/Error.h>

#include <EYEAST/Program.h>

#include <expected>

namespace Eye
{
	namespace Semantic
	{
		class Semantic
		{
		public:
			std::expected<bool, Error::Error> Validate(const std::shared_ptr<AST::Program>& ast);

		private:

		};
	}
}
