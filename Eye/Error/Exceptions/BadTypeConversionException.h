#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class BadTypeConversionException : public EyeException
			{
			public:
				BadTypeConversionException(const std::string& error, ErrorType errorType, const EyeSource& source)
					: EyeException("BadTypeConversionException: " + error, errorType, source)
				{
				}
			};
		}
	}
}
