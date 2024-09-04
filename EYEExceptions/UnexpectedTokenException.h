#pragma once

#include <stdexcept>
#include <string>

namespace Eye
{
	namespace Exceptions
	{
		class UnexpectedTokenException : public std::exception
		{
		public:
			UnexpectedTokenException(const std::string& token, size_t line, size_t col, const std::string& filepath);

			virtual const char* what() const noexcept override;

		private:
			std::string GetErrorLine(size_t line, size_t col, const std::string& filepath);

		private:
			std::string m_What;
		};
	}
}
