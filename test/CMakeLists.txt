find_package(GTest REQUIRED)

get_filename_component(AVL_TEST_INCLUDE_PATH "." ABSOLUTE)
get_filename_component(AVL_TEST_SOURCE_PATH "./${PROJECT_NAME}/test" ABSOLUTE)

set(AVL_TEST_TARGET "${PROJECT_NAME}-test")

file(GLOB_RECURSE AVL_TEST_SOURCES CONFIGURE_DEPENDS *.hpp *.cpp)

add_executable(${AVL_TEST_TARGET} ${AVL_TEST_SOURCES})

target_include_directories(${AVL_TEST_TARGET} PUBLIC ${AVL_TEST_INCLUDE_PATH})

target_link_libraries(
    ${AVL_TEST_TARGET} PRIVATE
    ${PROJECT_NAME}
    GTest::gtest
    GTest::gmock
)

gtest_discover_tests(${AVL_TEST_TARGET})
