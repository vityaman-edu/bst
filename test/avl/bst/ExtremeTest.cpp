#include <gtest/gtest.h>

#include "avl/bst/Example.hpp"
#include "avl/bst/Extreme.hpp"
#include "avl/bst/Search.hpp"

namespace avl::test {

TEST(BSTMin, Example) {
  auto [nodes, tree] = Example<int>();
  ASSERT_EQ(Min(tree, Search(tree, tree.Root(), 8)), Search(tree, tree.Root(), 1));
  ASSERT_EQ(Min(tree, Search(tree, tree.Root(), 3)), Search(tree, tree.Root(), 1));
  ASSERT_EQ(Min(tree, Search(tree, tree.Root(), 1)), Search(tree, tree.Root(), 1));
  ASSERT_EQ(Min(tree, Search(tree, tree.Root(), 6)), Search(tree, tree.Root(), 4));
  ASSERT_EQ(Min(tree, Search(tree, tree.Root(), 4)), Search(tree, tree.Root(), 4));
  ASSERT_EQ(Min(tree, Search(tree, tree.Root(), 7)), Search(tree, tree.Root(), 7));
  ASSERT_EQ(Min(tree, Search(tree, tree.Root(), 10)), Search(tree, tree.Root(), 10));
  ASSERT_EQ(Min(tree, Search(tree, tree.Root(), 14)), Search(tree, tree.Root(), 13));
  ASSERT_EQ(Min(tree, Search(tree, tree.Root(), 13)), Search(tree, tree.Root(), 13));
}

TEST(BSTMax, Example) {
  auto [nodes, tree] = Example<int>();
  ASSERT_EQ(Max(tree, Search(tree, tree.Root(), 8)), Search(tree, tree.Root(), 14));
  ASSERT_EQ(Max(tree, Search(tree, tree.Root(), 3)), Search(tree, tree.Root(), 7));
  ASSERT_EQ(Max(tree, Search(tree, tree.Root(), 1)), Search(tree, tree.Root(), 1));
  ASSERT_EQ(Max(tree, Search(tree, tree.Root(), 6)), Search(tree, tree.Root(), 7));
  ASSERT_EQ(Max(tree, Search(tree, tree.Root(), 4)), Search(tree, tree.Root(), 4));
  ASSERT_EQ(Max(tree, Search(tree, tree.Root(), 7)), Search(tree, tree.Root(), 7));
  ASSERT_EQ(Max(tree, Search(tree, tree.Root(), 10)), Search(tree, tree.Root(), 14));
  ASSERT_EQ(Max(tree, Search(tree, tree.Root(), 14)), Search(tree, tree.Root(), 14));
  ASSERT_EQ(Max(tree, Search(tree, tree.Root(), 13)), Search(tree, tree.Root(), 13));
}

}  // namespace avl::test