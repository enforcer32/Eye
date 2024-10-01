#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class CallException : public EyeException
			{
			public:
				CallException(const std::string& error, ErrorType errorType, const EyeSource& source)
					: EyeException("CallException: " + error, errorType, source)
				{
				}
			};
		}
	}
}
