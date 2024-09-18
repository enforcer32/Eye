#pragma once

#include "EYEError/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class BadTypeConversionException : public EyeException
			{
			public:
				BadTypeConversionException(const std::string& msg, const Utility::EyeSource& source)
					: EyeException("BadTypeConversionException: " + msg, source)
				{
				}
			};
		}
	}
}
