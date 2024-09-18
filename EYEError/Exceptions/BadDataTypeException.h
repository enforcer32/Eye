#pragma once

#include "EYEError/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class BadDataTypeException : public EyeException
			{
			public:
				BadDataTypeException(const std::string& msg, const Utility::EyeSource& source)
					: EyeException("BadDataTypeException: " + msg, source)
				{
				}
			};
		}
	}
}
