#pragma once

#include "EYEError/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class ReDeclarationException : public EyeException
			{
			public:
				ReDeclarationException(const std::string& msg, const Utility::EyeSource& source)
					: EyeException("ReDeclarationException: " + msg, source)
				{
				}
			};
		}
	}
}
