add_executable(Main Main.cpp)

add_dependencies(Main Creator Reporter)

add_custom_command(TARGET Main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Creator> ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Reporter> ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(Main PRIVATE "${CMAKE_SOURCE_DIR}/CMakOSLab1")
