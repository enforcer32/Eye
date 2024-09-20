file(GLOB_RECURSE TypeCheckerSources
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Type.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Type.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Environment.h"
)

target_sources(${EYE_TARGET_NAME} PRIVATE ${TypeCheckerSources})
