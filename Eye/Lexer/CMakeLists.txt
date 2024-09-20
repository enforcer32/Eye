file(GLOB_RECURSE LexerSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Token.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Token.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer.cpp"
)

target_sources(${EYE_TARGET_NAME} PRIVATE ${LexerSources})
