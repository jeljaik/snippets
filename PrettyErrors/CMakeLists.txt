cmake_minimum_required (VERSION 2.8.11)
SET(PROJECT_NAME "pretty-errors")
PROJECT(${PROJECT_NAME})

include_directories(MyClass.h errorsHelper.h)
add_executable(${PROJECT_NAME} main.cpp MyClass.cpp)
