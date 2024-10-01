#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class ReturnException : public EyeException
			{
			public:
				ReturnException(const std::string& error, ErrorType errorType, const EyeSource& source)
					: EyeException("ReturnException: " + error, errorType, source)
				{
				}
			};
		}
	}
}
