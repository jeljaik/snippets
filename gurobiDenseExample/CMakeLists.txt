cmake_minimum_required (VERSION 2.8.11)
set(PROJECTNAME "gurobi-test")
PROJECT(${PROJECTNAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(GUROBI REQUIRED)
find_package(Eigen REQUIRED)
find_package(EigenGurobi REQUIRED)

# set(EIGEN_GUROBI_INCLUDE_DIRS /usr/local/include/eigen-gurobi)
# set(EIGEN_GUROBI_LIBRARIES /usr/local/lib/libeigen-gurobi.dylib)
include_directories(${GUROBI_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS} ${EIGENGUROBI_INCLUDE_DIR})

add_executable(${PROJECTNAME} src/dense_c++.cpp)

target_link_libraries(${PROJECTNAME} ${GUROBI_LIBRARIES} ${EIGENGUROBI_LIBRARIES})
