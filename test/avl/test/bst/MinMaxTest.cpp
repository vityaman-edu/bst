#include <gtest/gtest.h>

#include "avl/bst/Extreme.hpp"
#include "avl/bst/Search.hpp"
#include "avl/test/bst/Example.hpp"

namespace avl::test {

TEST(BSTMin, Example) {
  auto [nodes, root] = Example();
  ASSERT_EQ(Min(Search(root, 8)), Search(root, 1));
  ASSERT_EQ(Min(Search(root, 3)), Search(root, 1));
  ASSERT_EQ(Min(Search(root, 1)), Search(root, 1));
  ASSERT_EQ(Min(Search(root, 6)), Search(root, 4));
  ASSERT_EQ(Min(Search(root, 4)), Search(root, 4));
  ASSERT_EQ(Min(Search(root, 7)), Search(root, 7));
  ASSERT_EQ(Min(Search(root, 10)), Search(root, 10));
  ASSERT_EQ(Min(Search(root, 14)), Search(root, 13));
  ASSERT_EQ(Min(Search(root, 13)), Search(root, 13));
}

TEST(BSTMax, Example) {
  auto [nodes, root] = Example();
  ASSERT_EQ(Max(Search(root, 8)), Search(root, 14));
  ASSERT_EQ(Max(Search(root, 3)), Search(root, 7));
  ASSERT_EQ(Max(Search(root, 1)), Search(root, 1));
  ASSERT_EQ(Max(Search(root, 6)), Search(root, 7));
  ASSERT_EQ(Max(Search(root, 4)), Search(root, 4));
  ASSERT_EQ(Max(Search(root, 7)), Search(root, 7));
  ASSERT_EQ(Max(Search(root, 10)), Search(root, 14));
  ASSERT_EQ(Max(Search(root, 14)), Search(root, 14));
  ASSERT_EQ(Max(Search(root, 13)), Search(root, 13));
}

}  // namespace avl::test