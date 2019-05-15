cmake_minimum_required (VERSION 3.12)

add_executable(SampleScript src/sample_script.cpp)
target_include_directories(SampleScript PRIVATE include/)
set_target_properties(SampleScript PROPERTIES CXX_STANDARD 17)

add_executable(UnitTest src/unit_test.cpp)
target_include_directories(UnitTest PRIVATE include/)
set_target_properties(UnitTest PROPERTIES CXX_STANDARD 17)
