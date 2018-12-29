cmake_minimum_required(VERSION 3.5)
project(tests C)

############################# options #############################

set(
  INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
file(
  GLOB_RECURSE SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
)
set(
  LIBS
  adsc
  ${CONAN_LIBS}
)

############################## target ##############################

setup_target("exe")