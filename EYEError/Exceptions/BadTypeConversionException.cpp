#include "EYEError/Exceptions/BadTypeConversionException.h"

#include <EYEUtility/FileIO.h>

#include <sstream>

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			BadTypeConversionException::BadTypeConversionException(const std::string& msg, const Types::Position& position)
				: std::exception()
			{
				m_What = "BadTypeConversionException: " + msg + "\n\ton line " + std::to_string(position.Line) + ", col " + std::to_string(position.Col) + " in file " + position.FilePath + "\n\t" + GetErrorLine(position.FilePath, position.Line, position.Col);
			}

			BadTypeConversionException::BadTypeConversionException(const std::string& msg, const Types::Location& location)
				: std::exception()
			{
				m_What = "BadTypeConversionException: " + msg + "\n\ton line " + std::to_string(location.Line) + ", col " + std::to_string(location.Col) + " in file " + location.FilePath + "\n\t" + GetErrorLine(location.FilePath, location.Line, location.Col);
			}

			const char* BadTypeConversionException::what() const noexcept
			{
				return m_What.c_str();
			}

			std::string BadTypeConversionException::GetErrorLine(const std::string& filepath, size_t line, size_t col)
			{
				std::istringstream dataStream = std::istringstream(Eye::FileIO::ReadFileContent(filepath));
				std::string dataLine;
				for (int i = 0; i < line; i++)
					std::getline(dataStream, dataLine);
				return dataLine;
			}
		}
	}
}
