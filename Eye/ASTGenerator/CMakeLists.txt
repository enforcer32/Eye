file(GLOB_RECURSE ASTGeneratorSources
	"${CMAKE_CURRENT_SOURCE_DIR}/ASTGenerator.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/ASTGenerator.cpp"
)

target_sources(${EYE_TARGET_NAME} PRIVATE ${ASTGeneratorSources})
