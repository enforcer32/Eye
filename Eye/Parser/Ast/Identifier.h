#pragma once

#include "Eye/Lexer/Token.h"

namespace EYE
{
	class IdentifierNode
	{
	public:
		IdentifierNode(Token identifier)
			: m_Identifier(identifier)
		{
		}

		std::string ToJSON() const
		{
			std::ostringstream oss;
			oss << "{\"Identifier\": {\n";
			oss << "\"type\": \"Identifier\",\n";
			oss << "\"value\": \"" << m_Identifier.String << "\"\n";
			oss << "}\n}";
			return oss.str();
		}

		std::string ToJSONSimple() const
		{
			std::ostringstream oss;
			oss << "\"Identifier\": {\n";
			oss << "\"type\": \"Identifier\",\n";
			oss << "\"value\": \"" << m_Identifier.String << "\"\n";
			oss << "}\n";
			return oss.str();
		}

	private:
		Token m_Identifier;
	};
}
