cmake_minimum_required(VERSION 3.30)

project(avl VERSION 0.1.0)

option(AVL_DEVELOPER "Enable ${PROJECT_NAME} developer mode" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(cmake/CompileOptions.cmake)

add_subdirectory(source)

if(AVL_DEVELOPER)
    add_subdirectory(test)
endif()
