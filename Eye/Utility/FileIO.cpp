#include "Eye/Utility/FileIO.h"
#include "Eye/Utility/Logger.h"

#include <fstream>
#include <sstream>

namespace Eye
{
	std::string FileIO::ReadFileContent(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		if (stream.fail())
			EYE_LOG_CRITICAL("Eye/Utility->FileIO->ReadFileContent Failed to Open({})", filepath);

		std::stringstream ss;
		std::string line;
		while (std::getline(stream, line))
			ss << line << "\n";

		stream.close();
		return ss.str();
	}

	void FileIO::WriteFileContent(const std::string& filepath, const std::string& data)
	{
		std::ofstream fout(filepath);
		fout << data.c_str();
	}
}
