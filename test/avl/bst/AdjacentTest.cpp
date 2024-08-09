#include <gtest/gtest.h>

#include "avl/bst/Adjacent.hpp"
#include "avl/bst/Example.hpp"
#include "avl/bst/Search.hpp"
#include "avl/bst/SimpleNode.hpp"

namespace avl::test {

TEST(BSTSuccessor, Example) {
  auto [nodes, root] = Example<SimpleNode<int>>();
  ASSERT_EQ(Successor(Search(root, 1)), Search(root, 3));
  ASSERT_EQ(Successor(Search(root, 3)), Search(root, 4));
  ASSERT_EQ(Successor(Search(root, 4)), Search(root, 6));
  ASSERT_EQ(Successor(Search(root, 6)), Search(root, 7));
  ASSERT_EQ(Successor(Search(root, 7)), Search(root, 8));
  ASSERT_EQ(Successor(Search(root, 8)), Search(root, 10));
  ASSERT_EQ(Successor(Search(root, 10)), Search(root, 13));
  ASSERT_EQ(Successor(Search(root, 13)), Search(root, 14));
  ASSERT_EQ(Successor(Search(root, 14)), nullptr);
}

TEST(BSTPredecessor, Example) {
  auto [nodes, root] = Example<SimpleNode<int>>();
  ASSERT_EQ(Predecessor(Search(root, 1)), nullptr);
  ASSERT_EQ(Predecessor(Search(root, 3)), Search(root, 1));
  ASSERT_EQ(Predecessor(Search(root, 4)), Search(root, 3));
  ASSERT_EQ(Predecessor(Search(root, 6)), Search(root, 4));
  ASSERT_EQ(Predecessor(Search(root, 7)), Search(root, 6));
  ASSERT_EQ(Predecessor(Search(root, 8)), Search(root, 7));
  ASSERT_EQ(Predecessor(Search(root, 10)), Search(root, 8));
  ASSERT_EQ(Predecessor(Search(root, 13)), Search(root, 10));
  ASSERT_EQ(Predecessor(Search(root, 14)), Search(root, 13));
}

}  // namespace avl::test
