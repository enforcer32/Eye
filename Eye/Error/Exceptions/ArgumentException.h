#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class ArgumentException : public EyeException
			{
			public:
				ArgumentException(const std::string& error, ErrorType errorType, const EyeSource& source)
					: EyeException("ArgumentException: " + error, errorType, source)
				{
				}
			};
		}
	}
}
