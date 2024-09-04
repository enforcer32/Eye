file(GLOB_RECURSE EYEExceptionsSources
	"${CMAKE_CURRENT_SOURCE_DIR}/UnexpectedTokenException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/UnexpectedTokenException.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/SyntaxErrorException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/SyntaxErrorException.cpp"
)

add_library(${EYEEXCEPTIONS_TARGET_NAME} STATIC ${EYEExceptionsSources})
target_include_directories(${EYEEXCEPTIONS_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_link_libraries(${EYEEXCEPTIONS_TARGET_NAME} PRIVATE ${EYEUTILITY_TARGET_NAME})
