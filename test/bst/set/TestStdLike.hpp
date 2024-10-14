#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <vector>

#include "bst/set/Set.hpp"
#include "bst/support/Ranges.hpp"

namespace bst::set {

using K = int;

template <template <class, class, class> class Tree>
void TestStdLike(const std::string& set_name) {  // NOLINT
  using Clock = std::chrono::high_resolution_clock;
  using SmartSet = std::set<K>;
  using SillySet = BSTSet<Tree, K>;

  const auto seed = 43278423342;

#ifdef NDEBUG
  const auto rounds = 5'000;
  const auto actions = 2'500;
  const auto freq = 500;
#else
  const auto rounds = 500;
  const auto actions = 500;
  const auto freq = 100;
#endif

  const K min = -100'000;
  const K max = +100'000;

  struct {
    std::size_t add = 0;
    std::size_t contains = 0;
    std::size_t lower_bound = 0;
    std::size_t upper_bound = 0;
    std::size_t remove = 0;
    std::size_t clear = 0;
    std::size_t size = 0;
    std::size_t iterate = 0;
  } statistics;

  std::uniform_int_distribution<int> coin(0, 1);
  std::uniform_int_distribution<int> key(min, max);

  const struct {
    int add = 100;
    int contains = 200;
    int lower_bound = 250;
    int upper_bound = 300;
    int remove = 400;
    int clear = 420;
    int size = 450;
    int iterate = 500;
  } border;
  std::uniform_int_distribution<int> action(0, border.iterate);

  std::default_random_engine random(seed);  // NOLINT

  auto begin = Clock::now();

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
      if (point < border.add) {
        statistics.add += 1;
        const auto val = random_key();
        silly.Add(val);
        smart.insert(val);
      } else if (point < border.contains) {
        statistics.contains += 1;
        const auto val = random_key();
        const auto silly_res = silly.Contains(val);
        const auto smart_res = smart.contains(val);
        ASSERT_EQ(silly_res, smart_res);
      } else if (point < border.lower_bound) {
        statistics.lower_bound += 1;
        const auto val = random_key();
        const auto silly_res = silly.LowerBound(val);
        const auto smart_res = smart.lower_bound(val);
        ASSERT_TRUE(
            (silly_res == silly.end() && smart_res == smart.end())  //
            || (*silly_res == *smart_res)
        );
      } else if (point < border.upper_bound) {
        statistics.upper_bound += 1;
        const auto val = random_key();
        const auto silly_res = silly.UpperBound(val);
        const auto smart_res = smart.upper_bound(val);
        ASSERT_TRUE(
            (silly_res == silly.end() && smart_res == smart.end())  //
            || (*silly_res == *smart_res)
        );
      } else if (point < border.remove) {
        statistics.remove += 1;
        const auto val = random_key();
        silly.Remove(val);
        smart.erase(val);
      } else if (point < border.clear) {
        statistics.clear += 1;
        silly.Clear();
        smart.clear();
      } else if (point < border.size) {
        statistics.size += 1;
        ASSERT_EQ(silly.Size(), smart.size());
      } else /* (point < border.iterate) */ {
        statistics.iterate += 1;
        const auto silly_items = ToVector<K>(silly);
        const auto smart_items = ToVector<K>(smart);
        ASSERT_EQ(silly_items, smart_items);
      }
    }
  }

  auto end = Clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

  std::cerr << "[ RUN      ] " << set_name << ".StdLike: statistics "  //
            << "duration " << duration << ", "                         //
            << "add = " << statistics.add << ", "                      //
            << "contains = " << statistics.contains << ", "            //
            << "lower_bound = " << statistics.lower_bound << ", "      //
            << "upper_bound = " << statistics.upper_bound << ", "      //
            << "remove = " << statistics.remove << ", "                //
            << "clear = " << statistics.clear << ", "                  //
            << "size = " << statistics.size << ", "                    //
            << "iterate = " << statistics.iterate << "." << std::endl;
}

}  // namespace bst::set