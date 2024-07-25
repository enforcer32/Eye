#include "Eye/Util/Logger.h"
#include "Eye/Common/Eye.h"

int main()
{
	EYE::Logger::Init();
	EYE_LOG_INFO("Eye");

	EYE::EyeProperties eyeProperties;
	eyeProperties.FilePath = "..\\..\\..\\..\\Examples\\Test.eye";

	EYE::Eye eye;
	if (eye.Run(eyeProperties) != EYE::EyeResult::Successful)
		EYE_LOG_CRITICAL("Failed to Run: File({})", eyeProperties.FilePath);

	EYE_LOG_INFO("EYE RAN SUCCESSFULLY!");
	return 0;
}
