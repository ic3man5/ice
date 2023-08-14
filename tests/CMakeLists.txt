set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(TARGET_NAME ice_tests)

project(${TARGET_NAME} LANGUAGES CXX)
message(STATUS "Tests being built")

add_executable(${TARGET_NAME} 
  tests.cpp 
  test_ice_exception.cpp 
  test_ice_library.cpp 
  test_ice_function.cpp 
  test_ice_library_manager.cpp
  test_ice_library_name.cpp)

#target_link_libraries(${TARGET_NAME}
#    PUBLIC test_ice_exception)

# https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(${TARGET_NAME})
target_link_libraries(${TARGET_NAME} Catch2WithMain)
target_link_libraries(${TARGET_NAME} ice)

add_subdirectory(testlib)
