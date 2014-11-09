# Copyright (C) 2014, Richard Thomson.  All rights reserved.
cmake_minimum_required(VERSION 2.8.11)
project(json-parser CXX)

# Locate Boost libraries: unit_test_framework
set(Boost_USE_DYNAMIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework)

add_executable(json-parser-test json.cpp json.h json_test.cpp)
target_include_directories(json-parser-test PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(json-parser-test ${Boost_LIBRARIES})
add_custom_command(TARGET json-parser-test POST_BUILD COMMAND json-parser-test)
