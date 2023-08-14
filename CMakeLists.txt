cmake_minimum_required(VERSION 3.21)
project(ice VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ice STATIC
        src/ice_library.cpp
        src/ice_library_manager.cpp 
        src/ice_library_name.cpp
)

target_include_directories(ice PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include/ice
)

target_include_directories(ice PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

#enable testing for the project
enable_testing()

add_subdirectory(tests)
