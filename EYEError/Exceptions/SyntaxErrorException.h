#pragma once

#include <EYETypes/Location.h>
#include <EYETypes/Position.h>

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
				SyntaxErrorException(const std::string& msg, const Types::Position& position);
				SyntaxErrorException(const std::string& msg, const Types::Location& location);

				virtual const char* what() const noexcept override;

			private:
				std::string GetErrorLine(const std::string& filepath, size_t line, size_t col);

			private:
				std::string m_What;
			};
		}
	}
}
