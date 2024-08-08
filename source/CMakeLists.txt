get_filename_component(AVL_INCLUDE_PATH "." ABSOLUTE)
get_filename_component(AVL_SOURCE_PATH "./${PROJECT_NAME}" ABSOLUTE)

set(
    AVL_SOURCES
    ${AVL_SOURCE_PATH}/Hello.cpp
)

add_library(${PROJECT_NAME} STATIC ${AVL_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${AVL_INCLUDE_PATH})
