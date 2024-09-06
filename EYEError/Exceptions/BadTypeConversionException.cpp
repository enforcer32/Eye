#include "EYEError/Exceptions/BadTypeConversionException.h"

#include <EYEUtility/FileIO.h>

#include <sstream>

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			BadTypeConversionException::BadTypeConversionException(const std::string& msg, const Utility::EyeSource& source)
				: std::exception()
			{
				m_What = "BadTypeConversionException: " + msg + "\n\ton line " + std::to_string(source.Line) + ", col " + std::to_string(source.Col) + " in " + Utility::EyeSourceTypeToString(source.Type) + " " + source.Source + "\n\t" + GetErrorLine(source);
			}

			const char* BadTypeConversionException::what() const noexcept
			{
				return m_What.c_str();
			}

			std::string BadTypeConversionException::GetErrorLine(const Utility::EyeSource& source)
			{
				std::istringstream dataStream = ((source.Type == Utility::EyeSourceType::File) ? std::istringstream(Eye::FileIO::ReadFileContent(source.Source)) : std::istringstream(source.Source));
				std::string dataLine;
				for (int i = 0; i < source.Line; i++)
					std::getline(dataStream, dataLine);
				return dataLine;
			}
		}
	}
}
