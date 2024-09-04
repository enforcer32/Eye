#include "EYEError/Exceptions/BadTypeConversionException.h"

#include <EYEUtility/FileIO.h>

#include <sstream>

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			BadTypeConversionException::BadTypeConversionException(const std::string& msg, size_t line, size_t col, const std::string& filepath)
				: std::exception()
			{
				m_What = "BadTypeConversionException: " + msg + "\n\ton line " + std::to_string(line) + ", col " + std::to_string(col) + " in file " + filepath + "\n\t" + GetErrorLine(line, col, filepath);
			}

			const char* BadTypeConversionException::what() const noexcept
			{
				return m_What.c_str();
			}

			std::string BadTypeConversionException::GetErrorLine(size_t line, size_t col, const std::string& filepath)
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
