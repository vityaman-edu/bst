#include <gtest/gtest.h>

#include <algorithm>
#include <random>

#include "bst/extra/BSTIndexedOrderedSet.hpp"
#include "bst/extra/NaiveIndexedOrderedSet.hpp"
#include "bst/naive/Tree.hpp"

namespace bst::extra {

using K = int;

using Node = naive::NaiveNode<K, TreeInfo>;
using Tree = naive::NaiveTree<K, TreeInfo, TreeInfo::Update<Node>>;

using SmartSet = BSTIndexedOrderedSet<Tree>;
using NaiveSet = NaiveIndexedOrderedSet<K>;

TEST(IndexedOrderedSet, Example) {
  const auto seed = 213121;
  std::default_random_engine random(seed);

  std::vector<int> elements = {0, 1, 2, 3, 4};
  std::ranges::shuffle(elements, random);

  SmartSet set;
  for (auto element : elements) {
    set.Add(element);
  }

  ASSERT_EQ(set.Size(), 5);
  ASSERT_EQ(set.At(0), 0);
  ASSERT_EQ(set.At(1), 1);
  ASSERT_EQ(set.At(2), 2);
  ASSERT_EQ(set.At(3), 3);
  ASSERT_EQ(set.At(4), 4);

  set.Add(-1);
  ASSERT_EQ(set.Size(), 6);
  ASSERT_EQ(set.At(0), -1);
  ASSERT_EQ(set.At(1), 0);

  // TODO(vityaman): not yet implemented
  // set.Remove(0);
  // ASSERT_EQ(set.Size(), 5);
  // ASSERT_EQ(set.At(0), -1);
  // ASSERT_EQ(set.At(1), 1);

  // set.Remove(2);
  // ASSERT_EQ(set.Size(), 4);
  // ASSERT_EQ(set.At(0), -1);
  // ASSERT_EQ(set.At(1), 1);
  // ASSERT_EQ(set.At(2), 3);
  // ASSERT_EQ(set.At(3), 4);

  // set.Remove(1);
  // ASSERT_EQ(set.Size(), 3);
  // ASSERT_EQ(set.At(0), -1);
  // ASSERT_EQ(set.At(1), 3);
}

TEST(IndexedOrderedSet, Comparison) {
  const auto seed = 43278423342;

#ifdef NDEBUG
  const auto rounds = 2'500;
  const auto actions = 1'000;
  const auto freq = 250;
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
    std::size_t remove = 0;
    std::size_t clear = 0;
    std::size_t size = 0;
    std::size_t at = 0;
    std::size_t iterate = 0;
  } statistics;

  std::uniform_int_distribution<int> coin(0, 1);
  std::uniform_int_distribution<int> key(min, max);

  const struct {
    int add = 200;
    int contains = 250;
    int remove = 250;
    int clear = 250;
    int size = 300;
    int iterate = 350;
  } border;

  std::uniform_int_distribution<int> action(0, border.iterate);

  std::default_random_engine random(seed);  // NOLINT

  for (auto i = 0; i < rounds; ++i) {
    if (i % freq == 0) {
      std::cerr << "[ RUN      ] " << "IndexedOrderedSet.Comparison: running round " << i << "..."
                << std::endl;
    }

    SmartSet smart;
    NaiveSet silly;

    const auto random_key = [&]() {
      if (smart.Size() == 0 || coin(random) == 0) {
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
        smart.Add(val);
      } else if (point < border.contains) {
        statistics.contains += 1;
        const auto val = random_key();
        const auto silly_res = silly.Contains(val);
        const auto smart_res = smart.Contains(val);
        ASSERT_EQ(silly_res, smart_res);
      } else if (point < border.remove) {
        statistics.remove += 1;
        const auto val = random_key();
        silly.Remove(val);
        smart.Remove(val);
      } else if (point < border.clear) {
        statistics.clear += 1;
        silly.Clear();
        smart.Clear();
      } else if (point < border.size) {
        statistics.size += 1;
        ASSERT_EQ(silly.Size(), smart.Size());
      } else /* (point < border.iterate) */ {
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
            << "clear = " << statistics.clear << ", "
            << "size = " << statistics.size << ", "
            << "iterate = " << statistics.iterate << "." << std::endl;
}

}  // namespace bst::extra