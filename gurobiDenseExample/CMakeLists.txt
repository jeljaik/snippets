cmake_minimum_required (VERSION 2.8.11)
set(PROJECTNAME "gurobi-test")
PROJECT(${PROJECTNAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(GUROBI REQUIRED)

include_directories(${GUROBI_INCLUDE_DIRS})

add_executable(${PROJECTNAME} src/dense_c++.cpp)

target_link_libraries(${PROJECTNAME} ${GUROBI_LIBRARIES})
