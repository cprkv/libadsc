cmake_minimum_required(VERSION 3.0)
project(adsc C)
project(adscd C)

# ------------ cmake and input configuration ------------

set(adsc_bin_install "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Installation directory for executables")
set(adsc_lib_install "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libraries")
set(adsc_inc_install "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installation directory for headers")

set(
    adsc_headers
    "include/adsc_base.h"
    "include/adsc_alloc.h"
    "include/adsc_lists.h"
    "include/adsc_vec.h"
    "include/adsc.h"
)
set(
    adsc_sources
    source/lists.c
    source/alloc.c
    source/vec.c
    source/algo.c
    ${adsc_headers}
    "include/adsc_internal.h"
)

# ------------ tuning compiler ------------

if(${CMAKE_C_COMPILER_ID} MATCHES "Clang")
    set(adsc_compiler_clang true)
    message("ADSC> using Clang compiler")
elseif(${CMAKE_C_COMPILER_ID} MATCHES "GNU")
    set(adsc_compiler_gnu true)
    message("ADSC> using GNU compiler")
else()
    message(FATAL_ERROR "ADSC is not ready to use with your compiler")
endif()

if(adsc_compiler_clang OR adsc_compiler_gnu)
    set(adsc_compile_flags_release -std=c11 -O3 -march=native -Wall)
    set(adsc_compile_flags_debug   -std=c11 -O0 -g -Wall -DDEBUG)
endif()

message("ADSC> debug flags   : ${adsc_compile_flags_debug}")
message("ADSC> release flags : ${adsc_compile_flags_release}")

# ------------ setting up libraries ------------

add_library(adsc ${adsc_sources})
target_compile_options(adsc PRIVATE ${adsc_compile_flags_release})
target_include_directories(adsc PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(adsc PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

add_library(adscd ${adsc_sources})
target_compile_options(adscd PRIVATE ${adsc_compile_flags_debug})
target_include_directories(adscd PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(adscd PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

install(
    TARGETS adsc
    LIBRARY DESTINATION "${adsc_lib_install}"
    ARCHIVE DESTINATION "${adsc_lib_install}"
)
install(
    TARGETS adscd
    LIBRARY DESTINATION "${adsc_lib_install}"
    ARCHIVE DESTINATION "${adsc_lib_install}"
)
install(
    FILES ${adsc_headers}
    DESTINATION "${adsc_inc_install}"
)
