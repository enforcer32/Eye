file(GLOB_RECURSE ParserSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp"
)

target_sources(${EYE_TARGET_NAME} PRIVATE ${ParserSources})
