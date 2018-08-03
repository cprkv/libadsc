cmake_minimum_required(VERSION 3.0)
project(adsc C)
project(adscd C)

# ------------ cmake and input configuration ------------

set(adsc_bin_install "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for executables")
set(adsc_lib_install "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libraries")
set(adsc_inc_install "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installation directory for headers")

set(
  adsc_headers
  "include/ads_base.h"
  "include/ads_alloc.h"
  "include/ads_list.h"
  "include/ads_dlist.h"
  "include/ads_vec.h"
  "include/ads_func.h"
  "include/ads.h"
)
set(
  adsc_sources
  source/lists.c
  source/alloc.c
  source/vec.c
  source/algo.c
  ${adsc_headers}
  "include/ads_internal.h"
)

# ------------ tuning compiler ------------
# remark: clang is first to check because if it is,
#         compiler_id says that is gnu too, but it's a lie!
if(${CMAKE_C_COMPILER_ID} MATCHES "Clang")
  message(FATAL_ERROR "adsc is not ready to use with your compiler")
elseif(${CMAKE_C_COMPILER_ID} MATCHES "GNU")
  message("adsc> using GNU compiler")
else()
  message(FATAL_ERROR "ADSC is not ready to use with your compiler")
endif()

set(adsc_compile_flags_release -std=gnu11 -O3 -march=native -Wall)
set(adsc_compile_flags_debug   -std=gnu11 -O0 -g -Wall -DDEBUG)
message("adsc> debug flags   : ${adsc_compile_flags_debug}")
message("adsc> release flags : ${adsc_compile_flags_release}")

# ------------ setting up libraries ------------

add_library(adsc ${adsc_sources})
target_compile_options(adsc PRIVATE ${adsc_compile_flags_release})
target_include_directories(adsc PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(adsc PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
)

add_library(adscd ${adsc_sources})
target_compile_options(adscd PRIVATE ${adsc_compile_flags_debug})
target_include_directories(adscd PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
set_target_properties(adscd PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
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
