#include "Eye/Utility/Logger.h"

#include <gtest/gtest.h>

int main(int argc, char** argv)
{
	Eye::Logger::Init();

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
