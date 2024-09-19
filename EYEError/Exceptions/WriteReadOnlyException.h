#pragma once

#include "EYEError/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class WriteReadOnlyException : public EyeException
			{
			public:
				WriteReadOnlyException(const std::string& msg, const Utility::EyeSource& source)
					: EyeException("WriteReadOnlyException: " + msg, source)
				{
				}
			};
		}
	}
}
