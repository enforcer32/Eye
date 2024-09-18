#pragma once

#include "EYEError/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class BadOperandTypeException : public EyeException
			{
			public:
				BadOperandTypeException(const std::string& msg, const Utility::EyeSource& source)
					: EyeException("BadOperandTypeException: " + msg, source)
				{
				}
			};
		}
	}
}
