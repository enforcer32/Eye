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
				BadTypeConversionException(const std::string& msg, const EyeSource& source)
					: EyeException("BadTypeConversionException: " + msg, source)
				{
				}
			};
		}
	}
}
