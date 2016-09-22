cmake_minimum_required(VERSION 2.8)

# train dispatching kit
project(TRK)

# cxx flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# include header files in include/
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# sources files
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)

add_executable(TRK ${SOURCES})