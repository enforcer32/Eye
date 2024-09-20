file(GLOB_RECURSE ASTSerializerSources
	"${CMAKE_CURRENT_SOURCE_DIR}/ASTSerializer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StringSerializer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/StringSerializer.cpp"
)

target_sources(${EYE_TARGET_NAME} PRIVATE ${ASTSerializerSources})
