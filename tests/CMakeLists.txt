cmake_minimum_required(VERSION 3.5)
project(tests C)

pkg_check_modules(CR REQUIRED criterion)

############################# options #############################

set(
  INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CR_INCLIDE_DIRS}
)
file(
  GLOB_RECURSE SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
)
set(
  LIBS
  adsc
  ${CR_LIBRARIES}
)

############################## target ##############################

setup_target("exe")