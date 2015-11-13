cmake_minimum_required(VERSION 2.8)

set(PROJECTNAME EstimatorsFactoryTest)
project(${PROJECTNAME})

file(GLOB src_dir    src/*.cpp)                     
file(GLOB include_dir include/*.h)

source_group("Source Files" FILES ${src_dir})
source_group("Header Files" FILES ${header_dir})

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(${PROJECTNAME} ${src_dir} ${include_dir})
