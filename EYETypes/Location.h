#pragma once

#include <string>

namespace Eye
{
	namespace Types
	{
		struct Location
		{
			size_t Line;
			size_t Col;
			size_t Start;
			size_t End;
			std::string FilePath;

			Location(size_t line = 1, size_t col = 1, size_t start = 1, size_t end = -1, const std::string& filePath = "")
				: Line(line), Col(col), Start(start), End(end), FilePath(filePath)
			{
			}

			std::string ToString() const
			{
				return "Location: {Line: " + std::to_string(Line) + ", Col: " + std::to_string(Col) + ", Start: " + std::to_string(Start) + ", End: " + std::to_string(End) + ", FilePath: " + FilePath + " }";
			}
		};
	}
}
