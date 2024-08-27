get_filename_component(BST_TEST_INCLUDE_PATH "." ABSOLUTE)
get_filename_component(BST_TEST_SOURCE_PATH "./${PROJECT_NAME}" ABSOLUTE)

set(BST_TEST_TARGET "${PROJECT_NAME}-test")

file(GLOB_RECURSE BST_TEST_SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_executable(${BST_TEST_TARGET} ${BST_TEST_SOURCES})

target_include_directories(${BST_TEST_TARGET} PUBLIC ${BST_TEST_INCLUDE_PATH})

target_link_libraries(
    ${BST_TEST_TARGET} PRIVATE
    ${PROJECT_NAME}
    GTest::gtest
    GTest::gmock
)

gtest_discover_tests(${BST_TEST_TARGET})
