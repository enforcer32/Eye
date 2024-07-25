#pragma once

#include <string>
#include <sstream>

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
