find_package(GBenchmark REQUIRED)

get_filename_component(BST_BENCH_SOURCE_PATH "./${PROJECT_NAME}" ABSOLUTE)

set(BST_BENCH_TARGET_BASE "${PROJECT_NAME}-bench")

macro(BST_BENCH_DECLARE suffix file)
    add_executable(
        ${BST_BENCH_TARGET_BASE}-${suffix}
        ${BST_BENCH_SOURCE_PATH}/${file}
    )

    target_link_libraries(
        ${BST_BENCH_TARGET_BASE}-${suffix}
        bst
        benchmark::benchmark
    )
endmacro()

BST_BENCH_DECLARE(avl AVL.cpp)
BST_BENCH_DECLARE(naive Naive.cpp)
