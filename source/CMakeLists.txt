get_filename_component(AVL_INCLUDE_PATH "." ABSOLUTE)
get_filename_component(AVL_SOURCE_PATH "./${PROJECT_NAME}" ABSOLUTE)

file(GLOB_RECURSE AVL_SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(${PROJECT_NAME} STATIC ${AVL_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${AVL_INCLUDE_PATH})
