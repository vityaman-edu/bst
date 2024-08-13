#include <gtest/gtest.h>

#include "avl/bst/Adjacent.hpp"
#include "avl/bst/Example.hpp"
#include "avl/bst/Search.hpp"

namespace avl::test {

TEST(BSTSuccessor, Example) {
  auto [nodes, tree] = Example<int>();
  ASSERT_EQ(Successor(tree, Search(tree, tree.Root(), 1)), Search(tree, tree.Root(), 3));
  ASSERT_EQ(Successor(tree, Search(tree, tree.Root(), 3)), Search(tree, tree.Root(), 4));
  ASSERT_EQ(Successor(tree, Search(tree, tree.Root(), 4)), Search(tree, tree.Root(), 6));
  ASSERT_EQ(Successor(tree, Search(tree, tree.Root(), 6)), Search(tree, tree.Root(), 7));
  ASSERT_EQ(Successor(tree, Search(tree, tree.Root(), 7)), Search(tree, tree.Root(), 8));
  ASSERT_EQ(Successor(tree, Search(tree, tree.Root(), 8)), Search(tree, tree.Root(), 10));
  ASSERT_EQ(Successor(tree, Search(tree, tree.Root(), 10)), Search(tree, tree.Root(), 13));
  ASSERT_EQ(Successor(tree, Search(tree, tree.Root(), 13)), Search(tree, tree.Root(), 14));
  ASSERT_EQ(Successor(tree, Search(tree, tree.Root(), 14)), tree.Nil());
}

TEST(BSTPredecessor, Example) {
  auto [nodes, tree] = Example<int>();
  ASSERT_EQ(Predecessor(tree, Search(tree, tree.Root(), 1)), tree.Nil());
  ASSERT_EQ(Predecessor(tree, Search(tree, tree.Root(), 3)), Search(tree, tree.Root(), 1));
  ASSERT_EQ(Predecessor(tree, Search(tree, tree.Root(), 4)), Search(tree, tree.Root(), 3));
  ASSERT_EQ(Predecessor(tree, Search(tree, tree.Root(), 6)), Search(tree, tree.Root(), 4));
  ASSERT_EQ(Predecessor(tree, Search(tree, tree.Root(), 7)), Search(tree, tree.Root(), 6));
  ASSERT_EQ(Predecessor(tree, Search(tree, tree.Root(), 8)), Search(tree, tree.Root(), 7));
  ASSERT_EQ(Predecessor(tree, Search(tree, tree.Root(), 10)), Search(tree, tree.Root(), 8));
  ASSERT_EQ(Predecessor(tree, Search(tree, tree.Root(), 13)), Search(tree, tree.Root(), 10));
  ASSERT_EQ(Predecessor(tree, Search(tree, tree.Root(), 14)), Search(tree, tree.Root(), 13));
}

}  // namespace avl::test
