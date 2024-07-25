#pragma once

#include <string>
#include <ostream>

namespace EYE
{
	struct Position
	{
		uint32_t Line = 1;
		uint32_t Col = 1;
		std::string FileName = "";

		friend std::ostream& operator<<(std::ostream& os, const Position& position)
		{
			os << "Position: {Line: " << position.Line << ", Column: " << position.Col << ", FileName: " << position.FileName << "}";
			return os;
		}

		std::string ToString() const
		{
			return "Position: {Line: " + std::to_string(Line) + ", Column: " + std::to_string(Col) + ", FileName: " + FileName + "}";
		}
	};
}
