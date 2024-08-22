file(GLOB_RECURSE EYETestSources
	"${CMAKE_CURRENT_SOURCE_DIR}/Test.cpp"

	# EYELexer
	"${CMAKE_CURRENT_SOURCE_DIR}/EYELexer/LiteralTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/EYELexer/KeywordTest.cpp"
)

add_executable(${EYETEST_TARGET_NAME} ${EYETestSources})
target_include_directories(${EYETEST_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE ${EYEUTILITY_TARGET_NAME})
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE ${EYELEXER_TARGET_NAME})
target_link_libraries(${EYETEST_TARGET_NAME} PRIVATE GTest::gtest_main)
