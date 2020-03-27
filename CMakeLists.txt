cmake_minimum_required(VERSION 3.9)
project(licensing)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # disables warning about DLL export 
  # this is annoying when using C++ STL
  add_compile_options(/wd4251)  
endif()

##################################################################
###### dependencies
##################################################################

add_subdirectory(dependencies)

##################################################################
###### licensing library
##################################################################

set(LICENSING_LIBRARY_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/licensing.cpp")
set(LICENSING_LIBRARY_HDR_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/licensing/licensing.h")

add_library(licensing SHARED ${LICENSING_LIBRARY_HDR_FILES} ${LICENSING_LIBRARY_SRC_FILES})
target_compile_definitions(licensing PRIVATE -DLIBLICENSING_BUILD_LIB)
target_include_directories(licensing PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(licensing PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/botan/build/include")
target_link_libraries(licensing botan)

set_target_properties(licensing PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(licensing PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

##################################################################
###### vendor library
##################################################################

if (NOT DEFINED LICENSING_VENDOR_LIBRARY_ENABLED)
  set(LICENSING_VENDOR_LIBRARY_ENABLED TRUE CACHE BOOL "whether the vendor library should be built")
endif()

if(LICENSING_VENDOR_LIBRARY_ENABLED)

  set(VENDOR_LIBRARY_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/vendor.cpp")
  set(VENDOR_LIBRARY_HDR_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/licensing/vendor.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/licensing/licensing.h")
  
  add_library(vendor SHARED ${VENDOR_LIBRARY_SRC_FILES} ${VENDOR_LIBRARY_HDR_FILES})
  target_compile_definitions(vendor PRIVATE -DLIBLICENSING_BUILD_LIB)
  target_include_directories(vendor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
  
  target_include_directories(vendor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/botan/build/include")
  target_link_libraries(vendor botan)
  
  set_target_properties(vendor PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
  set_target_properties(vendor PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

endif()

##################################################################
###### tests
##################################################################

if (NOT DEFINED LICENSING_TESTS_ENABLED)
  set(LICENSING_TESTS_ENABLED TRUE CACHE BOOL "whether the tests should be built")
endif()

if(LICENSING_TESTS_ENABLED) 
  add_subdirectory(tests)
endif()
