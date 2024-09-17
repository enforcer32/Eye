#include "EYEError/Exceptions/NotDeclaredException.h"

#include <EYEUtility/FileIO.h>

#include <sstream>

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			NotDeclaredException::NotDeclaredException(const std::string& msg, const Utility::EyeSource& source)
				: std::exception()
			{
				m_What = "NotDeclaredException: " + msg + "\n\ton line " + std::to_string(source.Line) + ", col " + std::to_string(source.Col) + " in " + Utility::EyeSourceTypeToString(source.Type) + " " + source.Source + "\n\t" + GetErrorLine(source);
			}

			const char* NotDeclaredException::what() const noexcept
			{
				return m_What.c_str();
			}

			std::string NotDeclaredException::GetErrorLine(const Utility::EyeSource& source)
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
