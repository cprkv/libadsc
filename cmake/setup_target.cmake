set(OBJ_DEFINED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/obj")
set(OBJ_DIR "${OBJ_DEFINED_DIR}" CACHE STRING "Build temp directory")
set(OUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin" CACHE STRING "Build output directory")

message("build temp directory: ${OBJ_DIR}")
message("build output directory: ${OUT_DIR}")

include(${OBJ_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

function(setup_target type)
  if(NOT CMAKE_COMPILER_IS_GNUCC)
    message(FATAL_ERROR "not GNU compilers are not supported yet by libadsc")
  endif()

  if(type STREQUAL "exe")
    add_executable(${PROJECT_NAME} ${SOURCES})
  elseif(type STREQUAL "lib")
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
  else()
    message(FATAL_ERROR "unknown target type: '${type}'")
  endif()

  target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
  target_link_libraries(
    ${PROJECT_NAME}
    ${LIBS}
  )

  message("[${PROJECT_NAME}] libraries: ${LIBS}")
  message("[${PROJECT_NAME}] includes: ${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}")

  set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR}
    C_STANDARD 11
    C_STANDARD_REQUIRED TRUE
    C_EXTENSIONS ON
    LINKER_LANGUAGE C
  )
endfunction(setup_target)