#pragma once

#include "EYEError/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class SyntaxErrorException : public EyeException
			{
			public:
				SyntaxErrorException(const std::string& msg, const Utility::EyeSource& source)
					: EyeException("SyntaxErrorException: " + msg, source)
				{
				}
			};
		}
	}
}
