#pragma once

#include <string>

namespace Eye
{
	namespace TypeChecker
	{
		enum class Type
		{
			Invalid,
			Integer,
			Float,
			String,
			Boolean,
		};

		std::string TypeToString(Type type);
	}
}
