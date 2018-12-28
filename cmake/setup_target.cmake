function(setup_target type)
  if (type STREQUAL "exe")
    add_executable(${PROJECT_NAME} ${SOURCES})
  elseif (type STREQUAL "lib")
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
  else ()
    message(FATAL_ERROR "unknown target type: '${type}'")
  endif ()

  target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
  )
  target_link_libraries(
    ${PROJECT_NAME}
    ${LIBS}
  )

  if (NOT CMAKE_COMPILER_IS_GNUCC)
    message(FATAL_ERROR "not GNU compilers are not supported yet by libadsc")
  endif ()

  set(OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

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