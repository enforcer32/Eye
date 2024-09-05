#pragma once

#include <string>

namespace Eye
{
	namespace Types
	{
		struct Position
		{
			size_t Line;
			size_t Col;
			size_t Offset;
			std::string FilePath;

			Position(size_t line = 1, size_t col = 1, size_t offset = 1, const std::string& filePath = "")
				: Line(line), Col(col), Offset(1), FilePath(filePath)
			{
			}

			std::string ToString() const
			{
				return "Position: {Line: " + std::to_string(Line) + ", Column: " + std::to_string(Col) + ", Offset: " + std::to_string(Offset) + ", FilePath: " + FilePath + "}";
			}
		};
	}
}
