#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class WriteReadOnlyException : public EyeException
			{
			public:
				WriteReadOnlyException(const std::string& error, ErrorType errorType, const EyeSource& source)
					: EyeException("WriteReadOnlyException: " + error, errorType, source)
				{
				}
			};
		}
	}
}
