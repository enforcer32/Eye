#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class BadOperandTypeException : public EyeException
			{
			public:
				BadOperandTypeException(const std::string& error, ErrorType errorType, const EyeSource& source)
					: EyeException("BadOperandTypeException: " + error, errorType, source)
				{
				}
			};
		}
	}
}
