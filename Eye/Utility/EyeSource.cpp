#include "Eye/Utility/EyeSource.h"

namespace Eye
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
