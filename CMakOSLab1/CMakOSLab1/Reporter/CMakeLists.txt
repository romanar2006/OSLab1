add_executable(Reporter Reporter.cpp)
include_directories(${CMAKE_SOURCE_DIR}/path_to_headers)
target_include_directories(Reporter PRIVATE "${CMAKE_SOURCE_DIR}/CMakOSLab1")
