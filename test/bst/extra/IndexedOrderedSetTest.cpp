#include <gtest/gtest.h>

#include <algorithm>
#include <random>

#include "bst/extra/BSTIndexedOrderedSet.hpp"
#include "bst/naive/Tree.hpp"

namespace bst::extra {

TEST(IndexedOrderedSet, Example) {
  using SmartSet = BSTIndexedOrderedSet<
      naive::NaiveTree<int, TreeInfo, TreeInfo::Update<naive::NaiveNode<int, TreeInfo>>>>;

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

}  // namespace bst::extra