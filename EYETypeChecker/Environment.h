#pragma once

#include <string>
#include <unordered_map>
#include <memory>

namespace Eye
{
	namespace TypeChecker
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

			void Define(const std::string& identifier, const T& value)
			{
				m_Values[identifier] = value;
			}

			void Assign(const std::string& identifier, const T& value)
			{
				AssignResolve(identifier, value);
			}

			const T& Get(const std::string& identifier)
			{
				return GetResolve(identifier);
			}

		private:
			const T& GetResolve(const std::string& identifier)
			{
				if (m_Values.find(identifier) != m_Values.end())
					return m_Values[identifier];
				else if (m_Parent)
					return m_Parent->GetResolve(identifier);
			}

			void AssignResolve(const std::string& identifier, const T& value)
			{
				if (m_Values.find(identifier) != m_Values.end())
					m_Values[identifier] = value;
				else if (m_Parent)
					m_Parent->AssignResolve(identifier, value);
			}

		private:
			std::shared_ptr<Environment> m_Parent = nullptr;
			std::unordered_map<std::string, T> m_Values;
		};
	}
}
