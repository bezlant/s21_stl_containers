cmake_minimum_required(VERSION 3.10)

project(
  STL
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
#set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()

file(GLOB SOURCES ./tests/*.cc)
add_executable(tests ${SOURCES})
target_compile_options(tests PRIVATE -Wall -Werror -Wextra -Wpedantic -O0)

target_link_libraries(tests GTest::gtest_main)

gtest_discover_tests(tests)
