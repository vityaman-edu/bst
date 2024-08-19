#include <benchmark/benchmark.h>

#include <string>

static void StringCreation(benchmark::State& state) {
  for (auto _ : state) {
    std::string created_string("hello");
    benchmark::DoNotOptimize(created_string);
  }
}

BENCHMARK(StringCreation);

BENCHMARK_MAIN();
