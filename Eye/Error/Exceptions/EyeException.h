#pragma once

#include "Eye/Utility/EyeSource.h"

#include <stdexcept>
#include <string>

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class EyeException : public std::exception
			{
			public:
				EyeException(const std::string& msg, const EyeSource& source);

				virtual const char* what() const noexcept override;

			private:
				std::string GetErrorLine(const EyeSource& source);

			private:
				std::string m_What;
			};
		}
	}
}
