#pragma once

#include "EYEError/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class BadTypeCompareException : public EyeException
			{
			public:
				BadTypeCompareException(const std::string& msg, const Utility::EyeSource& source)
					: EyeException("BadTypeCompareException: " + msg, source)
				{
				}
			};
		}
	}
}
