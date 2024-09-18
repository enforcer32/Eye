#pragma once

#include "EYEError/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class UnexpectedTokenException : public EyeException
			{
			public:
				UnexpectedTokenException(const std::string& msg, const Utility::EyeSource& source)
					: EyeException("UnexpectedTokenException: '" + msg + "'", source)
				{
				}
			};
		}
	}
}
