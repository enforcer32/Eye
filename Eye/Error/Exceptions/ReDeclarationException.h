#pragma once

#include "Eye/Error/Exceptions/EyeException.h"

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class ReDeclarationException : public EyeException
			{
			public:
				ReDeclarationException(const std::string& msg, const EyeSource& source)
					: EyeException("ReDeclarationException: " + msg, source)
				{
				}
			};
		}
	}
}
