file(GLOB_RECURSE EYETestSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Test.cpp"

	# EYELexer
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/LiteralTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/KeywordTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/SymbolTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/OperatorTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lexer/OtherTest.cpp"

	#EYEParser
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/StatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/ExpressionTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Parser/ExpressionErrorTest.cpp"

	#EYETypeChecker
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Statement/BlockStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Statement/VariableStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Statement/ControlStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Statement/IterationStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Statement/FunctionStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Expression/AssignmentExpressionTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Expression/CallExpressionTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Expression/UnaryExpressionTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Expression/PostfixExpressionTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Expression/BinaryExpression/BinaryExpressionArithmeticTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Expression/BinaryExpression/BinaryExpressionRelationalTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Expression/BinaryExpression/BinaryExpressionLogicalTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TypeChecker/Expression/BinaryExpression/BinaryExpressionBitwiseTest.cpp"

	#EYESemantic
	"${CMAKE_CURRENT_SOURCE_DIR}/Semantic/Statement/VariableStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Semantic/Statement/FunctionStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Semantic/Expression/CallExpressionTest.cpp"
)

add_executable(${EYETEST_TARGET_NAME} ${EYETestSources})
target_include_directories(${EYETEST_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE ${EYE_TARGET_NAME})
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE GTest::gtest_main)
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)
