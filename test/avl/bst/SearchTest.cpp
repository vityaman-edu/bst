#include <gtest/gtest.h>

#include "avl/bst/Example.hpp"
#include "avl/bst/Search.hpp"

namespace avl::test {

TEST(BSTSearch, Simple) {
  NodeFactory<Node> bst;

  auto* tree = bst(5, bst(4, bst(3)), bst(8, bst(6), bst(9)));

  ASSERT_NE(Search(tree, 3), nullptr);
  ASSERT_NE(Search(tree, 4), nullptr);
  ASSERT_NE(Search(tree, 5), nullptr);
  ASSERT_NE(Search(tree, 6), nullptr);
  ASSERT_NE(Search(tree, 8), nullptr);
  ASSERT_NE(Search(tree, 9), nullptr);

  ASSERT_EQ(Search(tree, 0), nullptr);
  ASSERT_EQ(Search(tree, 2), nullptr);
  ASSERT_EQ(Search(tree, 7), nullptr);
  ASSERT_EQ(Search(tree, 10), nullptr);
}

TEST(BSTSearch, Singleton) {
  Node node = {.key = 5};
  ASSERT_EQ(Search(&node, 5), &node);
  ASSERT_EQ(Search(&node, 0), nullptr);
  ASSERT_EQ(Search(&node, 10), nullptr);
}

}  // namespace avl::test
