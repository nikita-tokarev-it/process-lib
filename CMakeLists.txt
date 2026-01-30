cmake_minimum_required(VERSION 3.10)

project(ProcessLib)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(process_runner
    src/process_runner.cpp
)

add_executable(test_runner
    test/test_runner.cpp
)

target_link_libraries(test_runner process_runner)
