cmake_minimum_required(VERSION 2.8.9)
project (bos-boost-test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

file(GLOB source_dir src/main.cpp)
file(GLOB header_dir include/main.h)

find_package(Boost REQUIRED)
find_package(Eigen REQUIRED)

source_group("Source Files" FILES ${source_dir})
source_group("Header Files" FILES ${header_dir})

message("Boost_LIBRARY_DIRS: " ${Boost_LIBRARY_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Boost_INCLUDE_DIRS})
include_directories(${EIGEN_INCLUDE_DIRS})

add_executable(bos-boost-test ${source_dir} ${header_dir})
