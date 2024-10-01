#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class BadDataTypeException : public EyeException
			{
			public:
				BadDataTypeException(const std::string& error, ErrorType errorType, const EyeSource& source)
					: EyeException("BadDataTypeException: " + error, errorType, source)
				{
				}
			};
		}
	}
}
