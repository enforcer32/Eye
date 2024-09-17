#pragma once

#include <string>
#include <unordered_set>
#include <memory>

namespace Eye
{
	namespace Semantic
	{
		template<typename T>
		class Environment
		{
		public:
			Environment(const std::shared_ptr<Environment>& parent = nullptr)
				: m_Parent(parent)
			{
			}

			std::shared_ptr<Environment> GetParent() const
			{
				return m_Parent;
			}

			void Define(const T& value)
			{
				m_Values.insert(value);
			}

			bool Has(const T& value) const
			{
				if (m_Values.find(value) != m_Values.end())
					return true;
				else if (m_Parent)
					return m_Parent->Has(value);
				return false;
			}

		private:
			std::shared_ptr<Environment> m_Parent = nullptr;
			std::unordered_set<T> m_Values;
		};
	}
}
