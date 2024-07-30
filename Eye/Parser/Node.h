#pragma once

#include "Eye/Common/Common.h"

#include <iostream>
#include <vector>

namespace EYE
{
	/*
	struct Node;
	struct ProgramNode;
	struct StatementNode;
	struct ExpressionStatementNode;
	struct ExpressionNode;
	struct LiteralNode;

	enum class NodeType
	{
		Invalid,
		Program,
		ExpressionStatement,
		NumberLiteral,
		StringLiteral,
	};

	struct Node2
	{
		NodeType Type = NodeType::Invalid;
		Position Position;

		struct NodeMetadata
		{
			Node* Body = nullptr;
		} Metadata;

		union
		{
			char Char;
			const char* String;
			unsigned long long Number;
			void* Any;
		};

		Node2()
			: Any(nullptr)
		{
		}

		operator bool()
		{
			return Type != NodeType::Invalid;
		}

		friend std::ostream& operator<<(std::ostream& os, const Node& node)
		{
			bool printPosition = false;
			std::string type;
			std::string value = "None";

			switch (node.Type)
			{
			case NodeType::Invalid:
				type = "Invalid";
				break;
			case NodeType::Program:
				type = "Program";
				value = node.Metadata.Body->ToString();
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

			if(printPosition)
				os << "Node{Type: " << type << ", Value: " << value << ", Position: {Line: " << node.Position.Line << ", Column: " << node.Position.Col << ", FileName: " << node.Position.FileName << "}";
			else
				os << "Node{Type: " << type << ", Value: " << value << "}";
			return os;
		}

		std::string ToString() const
		{
			bool printPosition = false;
			std::string type;
			std::string value = "None";

			switch (Type)
			{
			case NodeType::Invalid:
				type = "Invalid";
				break;
			case NodeType::Program:
				type = "Program";
				break;
			case NodeType::Number:
				type = "Number";
				value = std::to_string(Number);
				break;
			case NodeType::String:
				type = "String";
				value = String;
				break;
			default:
				type = "UNKNOWN";
				break;
			}

			if(printPosition)
				return "Node{Type: " + type + ", Value: " + value + ", Position: {Line: " + std::to_string(Position.Line) + ", Column: " + std::to_string(Position.Col) + ", FileName: " + Position.FileName + "}";
			else
				return "Node{Type: " + type + ", Value: " + value + "}";
		}
	};*/
}
