file(GLOB_RECURSE EyeSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp"
	
	"${CMAKE_CURRENT_SOURCE_DIR}/Common/Common.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Common/Eye.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Common/Eye.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Token.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Lexer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Lexer.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Parser.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Parser.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Ast/ProgramNode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Ast/ExpressionNode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Ast/LiteralNode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Ast/BinaryExpressionNode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Ast/UnaryExpressionNode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Ast/AssignmentExpressionNode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Ast/LHSExpressionNode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Ast/StatementNode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/Ast/VariableDeclarationNode.h"

	"${CMAKE_CURRENT_SOURCE_DIR}/Util/Platform.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Util/Assertion.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Util/Logger.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Util/Logger.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Util/FileIO.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Util/FileIO.cpp"
)

file(GLOB_RECURSE EyeTestSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/Lexer/NumberTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/Lexer/StringTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/Lexer/OperatorTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/Lexer/SymbolTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/Lexer/CharacterTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/Lexer/SpecialTokenTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/Lexer/CommentTest.cpp"

	"${CMAKE_CURRENT_SOURCE_DIR}/Test/Parser/LiteralTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/Parser/StatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Test/Parser/ExpressionTest.cpp"
)

add_definitions(-DEYE_DEBUG)

add_executable(${EYE_TARGET_NAME} ${EyeSources} ${EyeTestSources})
target_include_directories(${EYE_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_include_directories(${EYE_TARGET_NAME} PRIVATE GTest::gtest_main)
target_link_libraries(${EYE_TARGET_NAME} PRIVATE spdlog)
target_link_libraries(${EYE_TARGET_NAME} PRIVATE GTest::gtest_main)
target_link_libraries(${EYE_TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)
