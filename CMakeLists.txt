cmake_minimum_required(VERSION 2.8)	
project(is_valid)

set(CMAKE_CXX_STANDARD 14)

enable_testing()
find_package(GTest REQUIRED)

include_directories(include)

add_library(Binary 
    src/Binary.cpp
    include/Binary.h
)

add_executable(test_binary test/test.cpp)

target_link_libraries(test_binary Binary GTest::GTest GTest::Main)

add_test(NAME BinaryTests COMMAND test_binary)