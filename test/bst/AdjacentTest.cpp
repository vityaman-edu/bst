#include <gtest/gtest.h>

#include "bst/Adjacent.hpp"
#include "bst/Example.hpp"
#include "bst/Search.hpp"

namespace bst {

TEST(BSTSuccessor, Example) {
  auto [nodes, tree] = Example<int>();
  ASSERT_EQ(Successor(Search(tree.Root(), 1)), Search(tree.Root(), 3));
  ASSERT_EQ(Successor(Search(tree.Root(), 3)), Search(tree.Root(), 4));
  ASSERT_EQ(Successor(Search(tree.Root(), 4)), Search(tree.Root(), 6));
  ASSERT_EQ(Successor(Search(tree.Root(), 6)), Search(tree.Root(), 7));
  ASSERT_EQ(Successor(Search(tree.Root(), 7)), Search(tree.Root(), 8));
  ASSERT_EQ(Successor(Search(tree.Root(), 8)), Search(tree.Root(), 10));
  ASSERT_EQ(Successor(Search(tree.Root(), 10)), Search(tree.Root(), 13));
  ASSERT_EQ(Successor(Search(tree.Root(), 13)), Search(tree.Root(), 14));
  ASSERT_EQ(Successor(Search(tree.Root(), 14)), nullptr);
}

TEST(BSTPredecessor, Example) {
  auto [nodes, tree] = Example<int>();
  ASSERT_EQ(Predecessor(Search(tree.Root(), 1)), nullptr);
  ASSERT_EQ(Predecessor(Search(tree.Root(), 3)), Search(tree.Root(), 1));
  ASSERT_EQ(Predecessor(Search(tree.Root(), 4)), Search(tree.Root(), 3));
  ASSERT_EQ(Predecessor(Search(tree.Root(), 6)), Search(tree.Root(), 4));
  ASSERT_EQ(Predecessor(Search(tree.Root(), 7)), Search(tree.Root(), 6));
  ASSERT_EQ(Predecessor(Search(tree.Root(), 8)), Search(tree.Root(), 7));
  ASSERT_EQ(Predecessor(Search(tree.Root(), 10)), Search(tree.Root(), 8));
  ASSERT_EQ(Predecessor(Search(tree.Root(), 13)), Search(tree.Root(), 10));
  ASSERT_EQ(Predecessor(Search(tree.Root(), 14)), Search(tree.Root(), 13));
}

}  // namespace bst
