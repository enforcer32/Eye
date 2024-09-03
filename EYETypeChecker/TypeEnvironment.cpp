#include "EYETypeChecker/TypeEnvironment.h"

#include <EYEUtility/Logger.h>

namespace Eye
{
	namespace TypeChecker
	{
		TypeEnvironment::TypeEnvironment(const std::shared_ptr<TypeEnvironment>& parent)
			: m_Parent(parent)
		{
		}

		std::shared_ptr<TypeEnvironment> TypeEnvironment::GetParent() const
		{
			return m_Parent;
		}

		void TypeEnvironment::DefineVariable(const std::string& identifier, Type value)
		{
			m_Variables[identifier] = value;
			EYE_LOG_INFO("EYETypeEnvironment->Defined Variable({}, {})", identifier, TypeToString(value));
		}

		void TypeEnvironment::AssignVariable(const std::string& identifier, Type value)
		{
			AssignResolveVariable(identifier, value);
			EYE_LOG_INFO("EYETypeEnvironment->Defined Assigned({}, {})", identifier, TypeToString(value));
		}

		Type TypeEnvironment::GetVariable(const std::string& identifier)
		{
			return GetResolveVariable(identifier);
		}

		Type TypeEnvironment::GetResolveVariable(const std::string& identifier)
		{
			if (m_Variables.find(identifier) != m_Variables.end())
				return m_Variables[identifier];
			else if (m_Parent)
				return m_Parent->GetResolveVariable(identifier);
		}

		void TypeEnvironment::AssignResolveVariable(const std::string& identifier, Type value)
		{
			if (m_Variables.find(identifier) != m_Variables.end())
				m_Variables[identifier] = value;
			else if (m_Parent)
				m_Parent->AssignResolveVariable(identifier, value);
		}
	}
}
