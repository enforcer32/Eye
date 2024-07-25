#pragma once

#include <string>

namespace EYE
{
	struct Position
	{
		uint32_t Line = 1;
		uint32_t Col = 1;
		std::string FileName = "";
	};
}
