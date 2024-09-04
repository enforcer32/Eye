#include "EYEError/Error.h"

namespace Eye
{
	namespace Error
	{
		Error::Error(ErrorType type, const std::string& message)
			: m_Type(type), m_Message(message)
		{
		}

		ErrorType Error::GetType() const
		{
			return m_Type;
		}

		std::string_view Error::GetMessage() const
		{
			return m_Message;
		}
	}
}
