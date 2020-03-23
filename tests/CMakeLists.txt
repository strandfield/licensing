
enable_testing()

add_executable(TEST_licensing "main.cpp")
add_dependencies(TEST_licensing licensing)
add_dependencies(TEST_licensing vendor)
target_include_directories(TEST_licensing PUBLIC "../include")
target_link_libraries(TEST_licensing licensing)
target_link_libraries(TEST_licensing vendor)

set_target_properties(TEST_licensing PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(TEST_licensing PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_test(NAME TEST_licensing COMMAND TEST_licensing)
