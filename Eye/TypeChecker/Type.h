#pragma once

#include <string>
#include <vector>

namespace Eye
{
	enum class Type
	{
		Integer,
		Float,
		String,
		Boolean,
		Void,
		Function,
	};

	std::string TypeToString(Type type);

	struct FunctionType
	{
		Type Return;
		std::vector<Type> Parameters;
	};
}
