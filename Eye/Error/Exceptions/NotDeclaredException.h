#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class NotDeclaredException : public EyeException
			{
			public:
				NotDeclaredException(const std::string& error, ErrorType errorType, const EyeSource& source)
					: EyeException("NotDeclaredException: " + error, errorType, source)
				{
				}
			};
		}
	}
}
