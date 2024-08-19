find_package(GBenchmark REQUIRED)

get_filename_component(AVL_BENCH_SOURCE_PATH "./${PROJECT_NAME}" ABSOLUTE)

set(AVL_BENCH_TARGET_BASE "${PROJECT_NAME}-bench")

add_executable(${AVL_BENCH_TARGET_BASE}-avl ${AVL_BENCH_SOURCE_PATH}/AVL.cpp)
target_link_libraries(${AVL_BENCH_TARGET_BASE}-avl benchmark::benchmark)
