#pragma once

namespace Eye
{
	enum class VariableTypeQualifier
	{
		None,
		Const,
	};

	enum class DeclarationType
	{
		Variable,
		Function
	};

	enum FunctionParameterType
	{
		Required,
		Default
	};

	struct FunctionDeclaration
	{
		std::vector<FunctionParameterType> Parameters;
	};
}
