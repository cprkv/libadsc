cmake_minimum_required(VERSION 3.0)
project(tests C)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

add_subdirectory(.. "adsc")

set(test_sources 
    lists.c
    alloc.c
    test_suite.c
    main.c
)

# message("Using GNU compiler")
# set(CMAKE_C_FLAGS            "${CMAKE_CXX_FLAGS}         -std=c11 -Wall -march=native ")
# set(CMAKE_C_FLAGS_DEBUG      "${CMAKE_CXX_FLAGS_DEBUG}   -O0 -g -DDEBUG")
# set(CMAKE_C_FLAGS_RELEASE    "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_executable(tests ${test_sources})
target_link_libraries(tests adsc)