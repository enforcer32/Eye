#pragma once

#include "EYETypeChecker/Type.h"

#include <string>
#include <unordered_map>
#include <memory>

namespace Eye
{
	namespace TypeChecker
	{
		class TypeEnvironment
		{
		public:
			TypeEnvironment(const std::shared_ptr<TypeEnvironment>& parent = nullptr);

			std::shared_ptr<TypeEnvironment> GetParent() const;
			bool DefineVariable(const std::string& identifier, Type value);
			void AssignVariable(const std::string& identifier, Type value);
			Type GetVariable(const std::string& identifier);

		private:
			Type GetResolveVariable(const std::string& identifier);
			void AssignResolveVariable(const std::string& identifier, Type value);

		private:
			std::shared_ptr<TypeEnvironment> m_Parent = nullptr;
			std::unordered_map<std::string, Type> m_Variables;
		};
	}
}
