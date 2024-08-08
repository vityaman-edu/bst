find_package(GTest REQUIRED)

get_filename_component(AVL_TEST_SOURCE_PATH "./${PROJECT_NAME}/test" ABSOLUTE)

set(AVL_TEST_TARGET "${PROJECT_NAME}-test")

set(
    AVL_TEST_SOURCES
    ${AVL_TEST_SOURCE_PATH}/MainTest.cpp
    ${AVL_TEST_SOURCE_PATH}/HelloTest.cpp
)

add_executable(${AVL_TEST_TARGET} ${AVL_TEST_SOURCES})

target_link_libraries(
    ${AVL_TEST_TARGET} PRIVATE
    ${PROJECT_NAME}
    GTest::gtest
    GTest::gmock
)
