cmake_minimum_required(VERSION 2.8.9)
project (Prototype)

file(GLOB source_dir src/main.cpp
                     src/SpotImage.cpp
                     src/LandSatImage.cpp
                     src/Image.cpp)
file(GLOB header_dir include/SpotImage.h
                     include/LandSatImage.h
                     include/Image.h)
                     
source_group("Source Files" FILES ${source_dir})
source_group("Header Files" FILES ${header_dir})

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(Prototype ${source_dir} ${header_dir})


