
set(LICENSING_SKIP_BOTAN_CONFIGURE FALSE CACHE BOOL "check if you want to skip botan configure.py")

if (NOT LICENSING_SKIP_BOTAN_CONFIGURE)

  file(DOWNLOAD https://github.com/randombit/botan/archive/2.13.0.zip "${CMAKE_CURRENT_LIST_DIR}/botan-2.13.0.zip" SHOW_PROGRESS)

  execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf botan-2.13.0.zip
                  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

  file(RENAME "${CMAKE_CURRENT_LIST_DIR}/botan-2.13.0" "${CMAKE_CURRENT_LIST_DIR}/botan")
  file(REMOVE "${CMAKE_CURRENT_LIST_DIR}/botan-2.13.0.zip")

  include(FindPythonInterp)

  message("Executing configure.py in ${CMAKE_CURRENT_LIST_DIR}/botan")
  
  string(TOLOWER ${CMAKE_CXX_COMPILER_ID} BOTAN_CC_OPT)
  
  execute_process(
                  COMMAND ${PYTHON_EXECUTABLE} "configure.py" "--cc=${BOTAN_CC_OPT}" "--disable-shared-library" "--with-cmake"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/botan"
                  RESULT_VARIABLE configure_py_result
                 )

  execute_process(
                  COMMAND ${PYTHON_EXECUTABLE} "patch_botan_cmakelists.py"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
                  RESULT_VARIABLE patch_botan_cmakelists_result
                 )

  if (NOT (patch_botan_cmakelists_result EQUAL 0))
    message(WARNING "Patching botan CMakeLists failed")
  endif()
                 
  set(LICENSING_SKIP_BOTAN_CONFIGURE TRUE CACHE BOOL "check if you want to skip botan configure.py" FORCE)
endif()

add_subdirectory(botan)
