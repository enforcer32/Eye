file(GLOB_RECURSE EyeSources
)

add_library(${EYE_TARGET_NAME} STATIC ${EyeSources})
target_include_directories(${EYE_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_link_libraries(${EYE_TARGET_NAME} PUBLIC spdlog)

add_subdirectory(Utility)
add_subdirectory(Error)
add_subdirectory(AST)
add_subdirectory(Lexer)
add_subdirectory(Parser)
#add_subdirectory(Semantic)
#add_subdirectory(TypeChecker)
add_subdirectory(ASTSerializer)
#add_subdirectory(ASTGenerator)
