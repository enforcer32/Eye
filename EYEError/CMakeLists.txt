file(GLOB_RECURSE EYEErrorSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Error.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Error.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/UnexpectedTokenException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/UnexpectedTokenException.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/SyntaxErrorException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/SyntaxErrorException.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/BadTypeConversionException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/BadTypeConversionException.cpp"
)

add_library(${EYEERROR_TARGET_NAME} STATIC ${EYEErrorSources})
target_include_directories(${EYEERROR_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_link_libraries(${EYEERROR_TARGET_NAME} PRIVATE ${EYEUTILITY_TARGET_NAME})
target_link_libraries(${EYEERROR_TARGET_NAME} PRIVATE ${EYETYPES_TARGET_NAME})
