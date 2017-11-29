cmake_minimum_required(VERSION 3.0)
project(tests C)
project(testsd C)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/.." "adsc")

set(tests_sources 
    lists.c
    alloc.c
    test_suite.c
    main.c
)

add_executable(tests ${tests_sources})
add_executable(testsd ${tests_sources})

message("tests> debug flags   : ${adsc_compile_flags_debug}")
message("tests> release flags : ${adsc_compile_flags_release}")

target_compile_definitions(tests PRIVATE ${adsc_compile_flags_release})
target_compile_definitions(testsd PRIVATE ${adsc_compile_flags_debug})

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