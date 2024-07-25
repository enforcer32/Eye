cmake_minimum_required(VERSION 3.28)

project(Eye
	VERSION 1.0.0
	LANGUAGES CXX
)

# CONFIGS
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EYE_TARGET_NAME Eye)

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

add_subdirectory(${EYE_TARGET_NAME})
