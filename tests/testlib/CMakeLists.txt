cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(libtest VERSION 0.0.1 DESCRIPTION "Test library")

option(TEST_BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)" ON)

set(SourceList src/test.cpp)

if (TEST_BUILD_SHARED_LIBS)
   add_library(libtest SHARED ${SourceList})
else()
   add_library(libtest STATIC ${SourceList})
endif()

set_target_properties(libtest PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/test.h)

target_include_directories(libtest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)