file(GLOB_RECURSE ErrorSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Error.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Error.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/EyeException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/EyeException.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/UnexpectedTokenException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/SyntaxErrorException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/BadTypeConversionException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/BadTypeCompareException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/BadOperandTypeException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/NotDeclaredException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/ReDeclarationException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/BadDataTypeException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/WriteReadOnlyException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/ReturnException.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/CallException.h"
)

target_sources(${EYE_TARGET_NAME} PRIVATE ${ErrorSources})
