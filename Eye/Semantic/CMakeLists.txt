file(GLOB_RECURSE SemanticSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Semantic.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Semantic.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/MapEnvironment.h"
)

target_sources(${EYE_TARGET_NAME} PRIVATE ${SemanticSources})
