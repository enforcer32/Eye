#pragma once

#include <string>
#include <unordered_set>
#include <memory>

namespace Eye
{
	namespace Semantic
	{
		template<typename T>
		class SetEnvironment
		{
		public:
			SetEnvironment(const std::shared_ptr<SetEnvironment>& parent = nullptr)
				: m_Parent(parent)
			{
			}

			std::shared_ptr<SetEnvironment> GetParent() const
			{
				return m_Parent;
			}

			void Define(const T& value)
			{
				m_Values.insert(value);
			}

			bool Has(const T& value, bool checkParent = true) const
			{
				if (m_Values.find(value) != m_Values.end())
					return true;
				else if (checkParent && m_Parent)
					return m_Parent->Has(value);
				return false;
			}

		private:
			std::shared_ptr<SetEnvironment> m_Parent = nullptr;
			std::unordered_set<T> m_Values;
		};
	}
}
