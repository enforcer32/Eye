#include "EYEUtility/EyeSource.h"

namespace Eye
{
	namespace Utility
	{
		const char* EyeSourceTypeToString(EyeSourceType type)
		{
			if (type == EyeSourceType::File)
				return "File";
			else if (type == EyeSourceType::String)
				return "String";
			return nullptr;
		}
	}
}
