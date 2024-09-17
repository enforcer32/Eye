#include "EYEError/Exceptions/ReDeclarationException.h"

#include <EYEUtility/FileIO.h>

#include <sstream>

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			ReDeclarationException::ReDeclarationException(const std::string& msg, const Utility::EyeSource& source)
				: std::exception()
			{
				m_What = "ReDeclarationException: " + msg + "\n\ton line " + std::to_string(source.Line) + ", col " + std::to_string(source.Col) + " in " + Utility::EyeSourceTypeToString(source.Type) + " " + source.Source + "\n\t" + GetErrorLine(source);
			}

			const char* ReDeclarationException::what() const noexcept
			{
				return m_What.c_str();
			}

			std::string ReDeclarationException::GetErrorLine(const Utility::EyeSource& source)
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
