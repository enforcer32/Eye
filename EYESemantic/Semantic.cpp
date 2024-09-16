#include "EYESemantic/Semantic.h"

namespace Eye
{
	namespace Semantic
	{
		std::expected<bool, Error::Error> Semantic::Validate(const std::shared_ptr<AST::Program>& ast)
		{
			return std::unexpected(Error::Error(Error::ErrorType::ParserSyntaxError, "Semantic Validation Failed"));
		}
	}
}
