cmake_minimum_required(VERSION 3.0)
project(tests C)
project(testsd C)

add_subdirectory(.. adsc)

set(tests_sources 
    lists.c
    alloc.c
    test_suite.c
    main.c
)

# ------------ tuning compiler ------------

if(${CMAKE_C_COMPILER_ID} MATCHES "Clang")
    set(tests_compiler_clang true)
    message("tests> using Clang compiler")
elseif(${CMAKE_C_COMPILER_ID} MATCHES "GNU")
    set(tests_compiler_gnu true)
    message("tests> using GNU compiler")
else()
    message(FATAL_ERROR "tests is not ready to use with your compiler")
endif()

if(tests_compiler_clang OR tests_compiler_gnu)
    set(tests_compile_flags_release -std=c11 -O3 -march=native -Wall)
    set(tests_compile_flags_debug   -std=c11 -O0 -g -Wall -DDEBUG)
endif()

message("tests> debug flags   : ${tests_compile_flags_debug}")
message("tests> release flags : ${tests_compile_flags_release}")

# ------------ setting up executables ------------

add_executable(tests ${tests_sources})
add_executable(testsd ${tests_sources})

target_compile_options(tests PRIVATE ${tests_compile_flags_release})
target_compile_options(testsd PRIVATE ${tests_compile_flags_debug})

set_target_properties(tests PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)
set_target_properties(testsd PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

target_link_libraries(tests adsc)
target_link_libraries(testsd adscd)