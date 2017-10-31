cmake_minimum_required(VERSION 3.0)
project(adsc C)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

set(sources 
    source/lists.c
    source/static.c
)

message("Using GNU compiler")
set(CMAKE_C_FLAGS            "${CMAKE_CXX_FLAGS}         -std=c11 -Wall -march=native ")
set(CMAKE_C_FLAGS_DEBUG      "${CMAKE_CXX_FLAGS_DEBUG}   -O0 -g")
set(CMAKE_C_FLAGS_RELEASE    "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_library(adsc ${sources})
target_include_directories(adsc PUBLIC include)