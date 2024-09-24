#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class ReturnException : public EyeException
			{
			public:
				ReturnException(const std::string& msg, const EyeSource& source)
					: EyeException("ReturnException: " + msg, source)
				{
				}
			};
		}
	}
}
