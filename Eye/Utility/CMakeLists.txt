file(GLOB_RECURSE UtilitySources
	"${CMAKE_CURRENT_SOURCE_DIR}/Platform.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Assertion.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Logger.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/FileIO.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/FileIO.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EyeSource.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/EyeSource.cpp"
)

target_sources(${EYE_TARGET_NAME} PRIVATE ${UtilitySources})
