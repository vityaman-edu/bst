#include <benchmark/benchmark.h>

#include <random>

#include "bst/naive/Tree.hpp"
#include "bst/set/Set.hpp"

namespace {

std::vector<int> RandomInput(std::size_t size) {
  const auto seed = 1432424;
  const auto min = -10'000;
  const auto max = +10'000;

  std::default_random_engine random(seed);
  std::uniform_int_distribution<int> number(min, max);

  std::vector<int> numbers(size);
  for (std::size_t i = 0; i < size; ++i) {
    numbers.emplace_back(number(random));
  }
  return numbers;
}

using Set = bst::set::BSTSet<bst::naive::NaiveTree, int>;

Set SetOf(const std::vector<int>& numbers) {
  Set set;
  for (auto number : numbers) {
    set.Add(number);
  }
  return set;
}

void LookupOnInputShuffled(benchmark::State& state) {
  const auto size = state.range(0);

  const auto input = RandomInput(size);
  auto set = SetOf(input);

  for (auto _ : state) {
    set.Contains(10);
  }

  state.SetComplexityN(size);
}

void LookupOnInputSorted(benchmark::State& state) {
  const auto size = state.range(0);

  const auto input = [&] {
    auto input = RandomInput(size);
    std::ranges::sort(input);
    return input;
  }();
  auto set = SetOf(input);

  for (auto _ : state) {
    set.Contains(10);
  }

  state.SetComplexityN(size);
}

}  // namespace

BENCHMARK(LookupOnInputShuffled)->RangeMultiplier(2)->Range(1 << 6, 1 << 12)->Complexity();
BENCHMARK(LookupOnInputSorted)->RangeMultiplier(2)->Range(1 << 6, 1 << 12)->Complexity();

BENCHMARK_MAIN();
