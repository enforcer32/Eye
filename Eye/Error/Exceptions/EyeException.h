#pragma once

#include "Eye/Utility/EyeSource.h"
#include "Eye/Error/Error.h"

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
				EyeException(const std::string& error, ErrorType errorType, const EyeSource& source);

				const Error& GetError() const;

				virtual const char* what() const noexcept override;

			private:
				std::string GetErrorLine(const EyeSource& source);

			private:
				Error m_Error;
			};
		}
	}
}
