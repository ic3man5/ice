cmake_minimum_required(VERSION 3.0)
project(ice VERSION 1.0.0 LANGUAGES CXX)

add_library(ice STATIC
        src/ice_library.cpp
        src/ice_library_manager.cpp
)

target_include_directories(ice PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include/ice
)

target_include_directories(ice PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/
)

target_compile_features(ice INTERFACE cxx_std_17)