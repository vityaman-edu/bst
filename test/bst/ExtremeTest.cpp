#include <gtest/gtest.h>

#include "bst/Example.hpp"
#include "bst/algo/Extreme.hpp"
#include "bst/algo/Search.hpp"

namespace bst {

TEST(BSTMin, Example) {
  auto [nodes, tree] = Example<int>();
  ASSERT_EQ(Min(Search(tree.Root(), 8)), Search(tree.Root(), 1));
  ASSERT_EQ(Min(Search(tree.Root(), 3)), Search(tree.Root(), 1));
  ASSERT_EQ(Min(Search(tree.Root(), 1)), Search(tree.Root(), 1));
  ASSERT_EQ(Min(Search(tree.Root(), 6)), Search(tree.Root(), 4));
  ASSERT_EQ(Min(Search(tree.Root(), 4)), Search(tree.Root(), 4));
  ASSERT_EQ(Min(Search(tree.Root(), 7)), Search(tree.Root(), 7));
  ASSERT_EQ(Min(Search(tree.Root(), 10)), Search(tree.Root(), 10));
  ASSERT_EQ(Min(Search(tree.Root(), 14)), Search(tree.Root(), 13));
  ASSERT_EQ(Min(Search(tree.Root(), 13)), Search(tree.Root(), 13));
}

TEST(BSTMax, Example) {
  auto [nodes, tree] = Example<int>();
  ASSERT_EQ(Max(Search(tree.Root(), 8)), Search(tree.Root(), 14));
  ASSERT_EQ(Max(Search(tree.Root(), 3)), Search(tree.Root(), 7));
  ASSERT_EQ(Max(Search(tree.Root(), 1)), Search(tree.Root(), 1));
  ASSERT_EQ(Max(Search(tree.Root(), 6)), Search(tree.Root(), 7));
  ASSERT_EQ(Max(Search(tree.Root(), 4)), Search(tree.Root(), 4));
  ASSERT_EQ(Max(Search(tree.Root(), 7)), Search(tree.Root(), 7));
  ASSERT_EQ(Max(Search(tree.Root(), 10)), Search(tree.Root(), 14));
  ASSERT_EQ(Max(Search(tree.Root(), 14)), Search(tree.Root(), 14));
  ASSERT_EQ(Max(Search(tree.Root(), 13)), Search(tree.Root(), 13));
}

}  // namespace bst