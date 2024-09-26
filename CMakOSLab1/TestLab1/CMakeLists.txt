cmake_minimum_required(VERSION 3.10)

project(TestLab1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Test)

set(CMAKE_AUTOMOC ON)

add_executable(TestLab1 tst_test1.cpp ${CMAKOSLAB1_SOURCES})

target_include_directories(TestLab1 PRIVATE ${CMAKE_SOURCE_DIR}/../CMakOSLab1)

target_link_libraries(TestLab1 PRIVATE Qt6::Test)
