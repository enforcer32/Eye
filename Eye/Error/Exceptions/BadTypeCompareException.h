#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class BadTypeCompareException : public EyeException
			{
			public:
				BadTypeCompareException(const std::string& msg, const EyeSource& source)
					: EyeException("BadTypeCompareException: " + msg, source)
				{
				}
			};
		}
	}
}
