#pragma once

#include <string>

namespace Eye
{
	enum class EyeSourceType
	{
		File,
		String,
	};
	const char* EyeSourceTypeToString(EyeSourceType type);

	struct EyeSource
	{
		std::string Source;
		EyeSourceType Type;
		size_t Line;
		size_t Col;
		size_t Start;
		size_t End;

		EyeSource(const std::string& source = "", EyeSourceType type = EyeSourceType::String, size_t line = 1, size_t col = 1, size_t start = 1, size_t end = -1)
			: Source(source), Type(type), Line(line), Col(col), Start(start), End(end)
		{
		}

		std::string ToString() const
		{
			return "EyeSource: {Source: " + Source + ", Type: " + EyeSourceTypeToString(Type) + ", Line: " + std::to_string(Line) + ", Col : " + std::to_string(Col) + ", Start : " + std::to_string(Start) + ", End : " + std::to_string(End) + "}";
		}
	};
}
