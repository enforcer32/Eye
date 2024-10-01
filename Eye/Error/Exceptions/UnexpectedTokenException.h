#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class UnexpectedTokenException : public EyeException
			{
			public:
				UnexpectedTokenException(const std::string& error, ErrorType errorType, const EyeSource& source)
					: EyeException("UnexpectedTokenException: '" + error + "'", errorType, source)
				{
				}
			};
		}
	}
}
