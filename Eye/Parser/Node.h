#pragma once

#include "Eye/Common/Common.h"

#include <iostream>

namespace EYE
{
	enum class NodeType
	{
		Invalid,
		Number,
		String,
	};

	struct Node
	{
		NodeType Type = NodeType::Invalid;
		Position Position;

		union
		{
			char Char;
			const char* String;
			unsigned long long Number;
			void* Any;
		};

		Node()
			: Any(nullptr)
		{
		}

		operator bool()
		{
			return Type != NodeType::Invalid;
		}

		friend std::ostream& operator<<(std::ostream& os, const Node& node)
		{
			std::string type;
			std::string value = "None";

			switch (node.Type)
			{
			case NodeType::Invalid:
				type = "Invalid";
				break;
			case NodeType::Number:
				type = "Number";
				value = std::to_string(node.Number);
				break;
			case NodeType::String:
				type = "String";
				value = node.String;
				break;
			default:
				type = "UNKNOWN";
				break;
			}

			os << "Node{Type: " << type << ", Value: " << value << ", Position: {Line: " << node.Position.Line << ", Column: " << node.Position.Col << ", FileName: " << node.Position.FileName << "}";
			return os;
		}
	};
}
