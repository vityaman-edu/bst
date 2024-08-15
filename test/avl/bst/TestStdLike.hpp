#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <ranges>
#include <set>
#include <vector>

#include "avl/bst/Set.hpp"

namespace avl::test {

using K = int;

template <BSTTree Tree>
void TestStdLike(const std::string& set_name) {  // NOLINT
  using SmartSet = std::set<K>;
  using SillySet = BSTSet<Tree>;

  const auto seed = 43278423342;
  const auto rounds = 1'000;
  const auto actions = 1'000;
  const auto freq = 100;
  const K min = 10;
  const K max = 99;

  struct {
    std::size_t add = 0;
    std::size_t contains = 0;
    std::size_t remove = 0;
    std::size_t iterate = 0;
  } statistics;

  std::uniform_int_distribution<int> coin(0, 1);
  std::uniform_int_distribution<int> key(min, max);
  std::uniform_int_distribution<int> action(0, 330);

  std::default_random_engine random(seed);  // NOLINT

  for (auto i = 0; i < rounds; ++i) {
    if (i % freq == 0) {
      std::cerr << "[ RUN      ] " << set_name << ".StdLike: running round " << i << "..."
                << std::endl;
    }

    SmartSet smart;
    SillySet silly;

    const auto random_key = [&]() {
      if (smart.size() == 0 || coin(random) == 0) {
        return key(random);
      }
      std::vector<int> out;
      std::ranges::sample(smart, std::back_inserter(out), 1, random);
      return out[0];
    };

    for (std::size_t j = 0; j < actions; ++j) {
      const auto point = action(random);
      if (point < 100) {
        statistics.add += 1;
        const auto val = random_key();
        silly.Add(val);
        smart.insert(val);
      } else if (point < 200) {
        statistics.contains += 1;
        const auto val = random_key();
        const auto silly_res = silly.Contains(val);
        const auto smart_res = smart.contains(val);
        ASSERT_EQ(silly_res, smart_res);
      } else if (point < 300 && set_name != "AVLSet") {
        statistics.remove += 1;
        const auto val = random_key();
        silly.Remove(val);
        smart.erase(val);
      } else {
        statistics.iterate += 1;
        const auto silly_items = silly | std::ranges::to<std::vector>();
        const auto smart_items = smart | std::ranges::to<std::vector>();
        ASSERT_EQ(silly_items, smart_items);
      }
    }
  }
  std::cerr << "[ RUN      ] SimpleSet.StdLike: statistics "
            << "add = " << statistics.add << ", "
            << "contains = " << statistics.contains << ", "
            << "remove = " << statistics.remove << ", "
            << "iterate = " << statistics.iterate << "." << std::endl;
}

}  // namespace avl::test