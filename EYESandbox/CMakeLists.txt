file(GLOB_RECURSE EYESandboxSources
	"${CMAKE_CURRENT_SOURCE_DIR}/EYESandbox.cpp"
)

add_executable(${EYESANDBOX_TARGET_NAME} ${EYESandboxSources})
target_include_directories(${EYESANDBOX_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../")
target_link_libraries(${EYESANDBOX_TARGET_NAME} PRIVATE ${EYE_TARGET_NAME})
