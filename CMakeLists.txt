cmake_minimum_required(VERSION 3.30)

project(bst VERSION 0.1.0)

option(BST_DEVELOPER "Enable ${PROJECT_NAME} developer mode" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(cmake/CompileOptions.cmake)

add_subdirectory(source)

if(BST_DEVELOPER)
    add_subdirectory(test)
    add_subdirectory(benchmark)
endif()
