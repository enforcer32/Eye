#pragma once

#include "EYEError/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class NotDeclaredException : public EyeException
			{
			public:
				NotDeclaredException(const std::string& msg, const Utility::EyeSource& source)
					: EyeException("NotDeclaredException: " + msg, source)
				{
				}
			};
		}
	}
}
