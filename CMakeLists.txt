cmake_minimum_required(VERSION 3.16)
project(StudentSort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optimised build by default (the benchmark results are meaningless without it).
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(studentsort ${SOURCES})
target_include_directories(studentsort PRIVATE include)

if(MSVC)
    target_compile_options(studentsort PRIVATE /W3)
else()
    target_compile_options(studentsort PRIVATE -Wall -Wextra)
endif()
