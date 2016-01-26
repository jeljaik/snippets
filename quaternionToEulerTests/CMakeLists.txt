cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(PROJECTNAME quaternionToEulerTests)
project(${PROJECTNAME})

find_package(Eigen3 REQUIRED)

file(GLOB src_dir    src/*.cpp)
file(GLOB include_dir include/*.h)

source_group("Source Files" FILES ${src_dir})
source_group("Header Files" FILES ${header_dir})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})
message("")
add_executable(${PROJECTNAME} ${src_dir} ${include_dir})
