#include "Eye/Util/Logger.h"
#include "Eye/Common/Eye.h"

#include <gtest/gtest.h>

int RunTests(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

int main(int argc, char** argv)
{
	EYE::Logger::Init();
	EYE_LOG_INFO("Eye");

	bool tests = true;
	if (tests)
		return RunTests(argc, argv);

	EYE::EyeProperties eyeProperties;
	eyeProperties.FilePath = "..\\..\\..\\..\\Examples\\Test.eye";

	EYE::Eye eye;
	if (eye.Run(eyeProperties) != EYE::EyeResult::Successful)
		EYE_LOG_CRITICAL("Failed to Run: File({})", eyeProperties.FilePath);

	return 0;
}
