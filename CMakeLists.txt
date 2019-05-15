cmake_minimum_required (VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

add_executable(SampleScript src/sample_script.cpp)
target_include_directories(SampleScript PRIVATE include/)

add_executable(UnitTest src/unit_test.cpp)
target_include_directories(UnitTest PRIVATE include/)
