file(GLOB_RECURSE EYETestSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Test.cpp"

	# EYELexer
	"${CMAKE_CURRENT_SOURCE_DIR}/EYELexer/LiteralTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYELexer/KeywordTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYELexer/SymbolTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYELexer/OperatorTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYELexer/OtherTest.cpp"

	#EYEParser
	"${CMAKE_CURRENT_SOURCE_DIR}/EYEParser/StatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYEParser/ExpressionTest.cpp"

	#EYETypeChecker
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Statement/BlockStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Statement/VariableStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Statement/ControlStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Statement/IterationStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Statement/FunctionStatementTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Expression/AssignmentExpressionTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Expression/CallExpressionTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Expression/UnaryExpressionTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Expression/PostfixExpressionTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Expression/BinaryExpression/BinaryExpressionArithmeticTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYETypeChecker/Expression/BinaryExpression/BinaryExpressionRelationalTest.cpp"
)

add_executable(${EYETEST_TARGET_NAME} ${EYETestSources})
target_include_directories(${EYETEST_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE ${EYEUTILITY_TARGET_NAME})
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE ${EYELEXER_TARGET_NAME})
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE ${EYEPARSER_TARGET_NAME})
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE ${EYETYPECHECKER_TARGET_NAME})
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE ${EYEASTGENERATOR_TARGET_NAME})
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE ${EYEASTSERIALIZER_TARGET_NAME})
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE GTest::gtest_main)
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)
