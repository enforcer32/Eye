#include "Eye/TypeChecker/Type.h"
#include "Eye/Utility/Logger.h"

namespace Eye
{
	std::string TypeToString(Type type)
	{
		switch (type)
		{
		case Eye::Type::Integer:
			return "Integer";
			break;
		case Eye::Type::Float:
			return "Float";
			break;
		case Eye::Type::String:
			return "String";
			break;
		case Eye::Type::Boolean:
			return "Boolean";
			break;
		case Eye::Type::Function:
			return "Function";
			break;
		default:
			EYE_LOG_CRITICAL("EYETypeToString Unknown Type!");
			break;
		}
	}
}
