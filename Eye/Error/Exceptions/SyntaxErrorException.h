#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class SyntaxErrorException : public EyeException
			{
			public:
				SyntaxErrorException(const std::string& error, ErrorType errorType, const EyeSource& source)
					: EyeException("SyntaxErrorException: " + error, errorType, source)
				{
				}
			};
		}
	}
}
