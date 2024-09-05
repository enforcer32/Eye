file(GLOB_RECURSE EYETypesSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Types.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Position.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Location.h"
)

add_library(${EYETYPES_TARGET_NAME} STATIC ${EYETypesSources})
target_include_directories(${EYETYPES_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
