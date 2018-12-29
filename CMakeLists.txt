cmake_minimum_required(VERSION 3.5)
project(ads)

find_package(PkgConfig REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(cmake/setup_target.cmake)

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

add_subdirectory(adsc)
add_subdirectory(tests)