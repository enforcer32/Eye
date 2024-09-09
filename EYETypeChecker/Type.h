#pragma once

#include <string>
#include <vector>

namespace Eye
{
	namespace TypeChecker
	{
		enum class Type
		{
			Integer,
			Float,
			String,
			Boolean,
			Void,
		};

		std::string TypeToString(Type type);

		struct FunctionType
		{
			Type Return;
			std::vector<Type> Parameters;
		};
	}
}
