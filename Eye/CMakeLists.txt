file(GLOB_RECURSE EyeSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp"
	
	"${CMAKE_CURRENT_SOURCE_DIR}/Common/Common.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Common/Eye.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Common/Eye.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Token.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Lexer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Lexer.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/Util/Platform.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Util/Assertion.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Util/Logger.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Util/Logger.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Util/FileIO.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Util/FileIO.cpp"
)

file(GLOB_RECURSE EyeTestSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/*.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/*.inl"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/**/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/**/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/**/*.cxx"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/**/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/**/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/**/*.inl"
)

add_definitions(-DEYE_DEBUG)

add_executable(${EYE_TARGET_NAME} ${EyeSources} ${EyeTestSources})
target_include_directories(${EYE_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_include_directories(${EYE_TARGET_NAME} PRIVATE GTest::gtest_main)
target_link_libraries(${EYE_TARGET_NAME} PRIVATE spdlog)
target_link_libraries(${EYE_TARGET_NAME} PRIVATE GTest::gtest_main)
