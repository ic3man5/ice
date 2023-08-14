cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(TARGET_NAME simple_test)

project(${TARGET_NAME} VERSION 0.0.1 DESCRIPTION "Test library")

option(TEST_BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)" ON)

set(SourceList src/test.cpp)

if (TEST_BUILD_SHARED_LIBS)
   add_library(${TARGET_NAME} SHARED ${SourceList})
else()
   add_library(${TARGET_NAME} STATIC ${SourceList})
endif()

set_target_properties(${TARGET_NAME} PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/test.h)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES PREFIX "")