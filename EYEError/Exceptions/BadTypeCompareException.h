#pragma once

#include <EYEUtility/EyeSource.h>

#include <stdexcept>
#include <string>

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class BadTypeCompareException : public std::exception
			{
			public:
				BadTypeCompareException(const std::string& msg, const Utility::EyeSource& source);

				virtual const char* what() const noexcept override;

			private:
				std::string GetErrorLine(const Utility::EyeSource& source);

			private:
				std::string m_What;
			};
		}
	}
}
