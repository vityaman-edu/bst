#include <gtest/gtest.h>

#include <algorithm>
#include <random>

#include "bst/avl/Tree.hpp"
#include "bst/set/IndexedBSTSet.hpp"
#include "bst/set/NaiveIndexedOrderedSet.hpp"
#include "bst/support/Ranges.hpp"

namespace bst::set {

using K = int;

using SmartSet = IndexedBSTSet<avl::AVLTree, K>;
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

  set.Remove(0);
  ASSERT_EQ(set.Size(), 5);
  ASSERT_EQ(set.At(0), -1);
  ASSERT_EQ(set.At(1), 1);

  set.Remove(2);
  ASSERT_EQ(set.Size(), 4);
  ASSERT_EQ(set.At(0), -1);
  ASSERT_EQ(set.At(1), 1);
  ASSERT_EQ(set.At(2), 3);
  ASSERT_EQ(set.At(3), 4);

  set.Remove(1);
  ASSERT_EQ(set.Size(), 3);
  ASSERT_EQ(set.At(0), -1);
  ASSERT_EQ(set.At(1), 3);
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
    int add = 100;
    int contains = 200;
    int remove = 300;
    int clear = 325;
    int size = 350;
    int at = 450;
    int iterate = 500;
  } border;

  std::uniform_int_distribution<int> action(0, border.iterate);

  std::default_random_engine random(seed);  // NOLINT

  for (auto i = 0; i < rounds; ++i) {
    if (i % freq == 0) {
      std::cerr << "[ RUN      ] " << "IndexedOrderedSet.Comparison: running round " << i << "..."
                << std::endl;
    }

    SmartSet smart;
    NaiveSet naive;

    const auto random_key = [&]() {
      if (smart.Size() == 0 || coin(random) == 0) {
        return key(random);
      }
      std::vector<int> out;
      std::ranges::sample(smart, std::back_inserter(out), 1, random);
      return out[0];
    };

    const auto random_index = [&]() {
      std::uniform_int_distribution<std::size_t> index(0, smart.Size() - 1);
      return index(random);
    };

    for (std::size_t j = 0; j < actions; ++j) {
      const auto point = action(random);
      if (point < border.add) {
        statistics.add += 1;
        const auto val = random_key();
        naive.Add(val);
        smart.Add(val);
      } else if (point < border.contains) {
        statistics.contains += 1;
        const auto val = random_key();
        const auto naive_res = naive.Contains(val);
        const auto smart_res = smart.Contains(val);
        ASSERT_EQ(naive_res, smart_res);
      } else if (point < border.remove) {
        statistics.remove += 1;
        const auto val = random_key();
        naive.Remove(val);
        smart.Remove(val);
      } else if (point < border.clear) {
        statistics.clear += 1;
        naive.Clear();
        smart.Clear();
      } else if (point < border.size) {
        statistics.size += 1;
        ASSERT_EQ(naive.Size(), smart.Size());
      } else if (point < border.at && !smart.IsEmpty()) {
        statistics.at += 1;
        const auto index = random_index();
        ASSERT_EQ(naive.At(index), smart.At(index));
      } else /* (point < border.iterate) */ {
        statistics.iterate += 1;
        const auto naive_items = ToVector<K>(naive);
        const auto smart_items = ToVector<K>(smart);
        ASSERT_EQ(naive_items, smart_items);
      }
    }
  }

  std::cerr << "[ RUN      ] SimpleSet.StdLike: statistics "  //
            << "add = " << statistics.add << ", "             //
            << "contains = " << statistics.contains << ", "   //
            << "remove = " << statistics.remove << ", "       //
            << "clear = " << statistics.clear << ", "         //
            << "size = " << statistics.size << ", "           //
            << "at = " << statistics.at << ", "               //
            << "iterate = " << statistics.iterate << "." << std::endl;
}

}  // namespace bst::set