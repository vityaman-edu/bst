find_package(GBenchmark REQUIRED)

get_filename_component(AVL_BENCH_SOURCE_PATH "./${PROJECT_NAME}" ABSOLUTE)

set(AVL_BENCH_TARGET_BASE "${PROJECT_NAME}-bench")

macro(AVL_BENCH_DECLARE suffix file)
    add_executable(
        ${AVL_BENCH_TARGET_BASE}-${suffix}
        ${AVL_BENCH_SOURCE_PATH}/${file}
    )

    target_link_libraries(
        ${AVL_BENCH_TARGET_BASE}-${suffix}
        bst
        benchmark::benchmark
    )
endmacro()

AVL_BENCH_DECLARE(avl AVL.cpp)
AVL_BENCH_DECLARE(naive Naive.cpp)
