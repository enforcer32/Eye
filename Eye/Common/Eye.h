#pragma once

#include "Eye/Lexer/Token.h"

#include <string>
#include <sstream>
#include <vector>

namespace EYE
{
	struct EyeProperties
	{
		std::string FilePath;
	};

	struct EyeInstance
	{
		std::string InFilePath;
		std::istringstream InFileStream;
		std::vector<Token> LexerTokens;
	};

	enum class EyeResult
	{
		Successful,
		Failed
	};

	class Eye
	{
	public:
		EyeResult Run(const EyeProperties& properties);

	private:
		EyeProperties m_Properties;
		EyeInstance* m_EyeInstance;
	};
}
