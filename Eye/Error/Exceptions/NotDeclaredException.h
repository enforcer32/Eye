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
				NotDeclaredException(const std::string& msg, const EyeSource& source)
					: EyeException("NotDeclaredException: " + msg, source)
				{
				}
			};
		}
	}
}
