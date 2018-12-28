cmake_minimum_required(VERSION 3.5)
project(adsc C)

############################# options #############################

file(
  GLOB_RECURSE SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIBS)

############################## target ##############################

setup_target("lib")