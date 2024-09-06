#pragma once

#include <string>

namespace Eye
{
	namespace Error
	{
		enum class ErrorType
		{
			LexerUnexpectedToken,
			ParserSyntaxError,
			TypeCheckerBadTypeConversion,
			TypeCheckerBadTypeCompare,
		};

		class Error
		{
		public:
			Error(ErrorType type, const std::string& message);

			ErrorType GetType() const;
			std::string_view GetMessage() const;

		private:
			ErrorType m_Type;
			std::string m_Message;
		};
	}
}
