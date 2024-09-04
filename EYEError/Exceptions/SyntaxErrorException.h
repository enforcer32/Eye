#pragma once

#include <stdexcept>
#include <string>

namespace Eye
{
	namespace Error
	{
		namespace Exceptions
		{
			class SyntaxErrorException : public std::exception
			{
			public:
				SyntaxErrorException(const std::string& msg, size_t line, size_t col, const std::string& filepath);

				virtual const char* what() const noexcept override;

			private:
				std::string GetErrorLine(size_t line, size_t col, const std::string& filepath);

			private:
				std::string m_What;
			};
		}
	}
}
