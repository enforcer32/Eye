#pragma once

#include "Eye/Utility/Logger.h"

#include <string>
#include <unordered_map>
#include <memory>

namespace Eye
{
	template<typename T>
	class MapEnvironment
	{
	public:
		MapEnvironment(const std::shared_ptr<MapEnvironment>& parent = nullptr)
			: m_Parent(parent)
		{
		}

		std::shared_ptr<MapEnvironment> GetParent() const
		{
			return m_Parent;
		}

		void Define(const std::string& identifier, const T& value)
		{
			m_Values[identifier] = value;
		}

		void Assign(const std::string& identifier, const T& value)
		{
			if (m_Values.find(identifier) != m_Values.end())
				m_Values[identifier] = value;
			else if (m_Parent)
				m_Parent->Assign(identifier, value);

			EYE_LOG_CRITICAL("MapEnvironment->Assign " + identifier + " Not Defined!");
		}

		const T& Get(const std::string& identifier)
		{
			if (m_Values.find(identifier) != m_Values.end())
				return m_Values[identifier];
			else if (m_Parent)
				return m_Parent->Get(identifier);

			EYE_LOG_CRITICAL("MapEnvironment->Get " + identifier + " Not Defined!");
		}

		bool Has(const std::string& identifier, bool checkParent = true) const
		{
			if (m_Values.find(identifier) != m_Values.end())
				return true;
			else if (checkParent && m_Parent)
				return m_Parent->Has(identifier);
			return false;
		}

	private:
		std::shared_ptr<MapEnvironment> m_Parent = nullptr;
		std::unordered_map<std::string, T> m_Values;
	};
}
