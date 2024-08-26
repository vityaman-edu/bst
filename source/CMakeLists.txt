get_filename_component(BST_INCLUDE_PATH "." ABSOLUTE)
get_filename_component(BST_SOURCE_PATH "./${PROJECT_NAME}" ABSOLUTE)

file(GLOB_RECURSE BST_SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_library(${PROJECT_NAME} STATIC ${BST_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${BST_INCLUDE_PATH})
