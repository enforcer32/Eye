#include "EYETypeChecker/Type.h"

#include <EYEUtility/Logger.h>

namespace Eye
{
	namespace TypeChecker
	{
		std::string TypeToString(Type type)
		{
			switch (type)
			{
			case Eye::TypeChecker::Type::Integer:
				return "Integer";
				break;
			case Eye::TypeChecker::Type::Float:
				return "Float";
				break;
			case Eye::TypeChecker::Type::String:
				return "String";
				break;
			case Eye::TypeChecker::Type::Boolean:
				return "Boolean";
				break;
			default:
				EYE_LOG_CRITICAL("EYETypeToString Unknown Type!");
				break;
			}
		}
	}
}
