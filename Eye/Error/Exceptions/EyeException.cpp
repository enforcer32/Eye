#include "Eye/Error/Exceptions/EyeException.h"
#include "Eye/Utility/FileIO.h"

#include <sstream>

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			EyeException::EyeException(const std::string& msg, const EyeSource& source)
				: std::exception()
			{
				m_What = msg + "\n\ton line " + std::to_string(source.Line) + ", col " + std::to_string(source.Col) + " in " + EyeSourceTypeToString(source.Type) + " " + source.Source + "\n\t" + GetErrorLine(source);
			}

			const char* EyeException::what() const noexcept
			{
				return m_What.c_str();
			}

			std::string EyeException::GetErrorLine(const EyeSource& source)
			{
				std::istringstream dataStream = ((source.Type == EyeSourceType::File) ? std::istringstream(Eye::FileIO::ReadFileContent(source.Source)) : std::istringstream(source.Source));
				std::string dataLine;
				for (int i = 0; i < source.Line; i++)
					std::getline(dataStream, dataLine);
				return dataLine;
			}
		}
	}
}
