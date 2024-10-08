cmake_minimum_required(VERSION 3.28)

project(Eye
	VERSION 1.0.0
	LANGUAGES CXX
)

# CONFIGS
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EYE_TARGET_NAME Eye)
set(EYESANDBOX_TARGET_NAME EyeSandbox)
set(EYETEST_TARGET_NAME EyeTest)

# Extensions
include(FetchContent)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY "https://github.com/gabime/spdlog"
        GIT_TAG "v1.14.1"
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest"
        GIT_TAG "v1.14.0"
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
        cpplinenoise
        GIT_REPOSITORY "https://github.com/yhirose/cpp-linenoise"
        GIT_TAG "master"
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(cpplinenoise)

add_subdirectory(${EYE_TARGET_NAME})
add_subdirectory(${EYESANDBOX_TARGET_NAME})
add_subdirectory(${EYETEST_TARGET_NAME})
