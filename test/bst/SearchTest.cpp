#include <gtest/gtest.h>

#include "bst/Example.hpp"
#include "bst/Search.hpp"
#include "bst/naive/Node.hpp"
#include "bst/naive/Tree.hpp"

namespace bst {

TEST(BSTSearch, Simple) {
  NaiveNodeFactory<int> bst;

  NaiveTree<int> tree;
  auto* root = bst(5, bst(4, bst(3)), bst(8, bst(6), bst(9)));

  ASSERT_EQ(Search(tree, root, 3)->key, 3);
  ASSERT_EQ(Search(tree, root, 4)->key, 4);
  ASSERT_EQ(Search(tree, root, 5)->key, 5);
  ASSERT_EQ(Search(tree, root, 6)->key, 6);
  ASSERT_EQ(Search(tree, root, 8)->key, 8);
  ASSERT_EQ(Search(tree, root, 9)->key, 9);

  ASSERT_EQ(Search(tree, root, 0), nullptr);
  ASSERT_EQ(Search(tree, root, 2), nullptr);
  ASSERT_EQ(Search(tree, root, 7), nullptr);
  ASSERT_EQ(Search(tree, root, 10), nullptr);
}

TEST(BSTSearch, Singleton) {
  NaiveTree<int> tree;
  NaiveNode<int> node = {.key = 5};
  ASSERT_EQ(Search(tree, &node, 5), &node);
  ASSERT_EQ(Search(tree, &node, 0), nullptr);
  ASSERT_EQ(Search(tree, &node, 10), nullptr);
}

}  // namespace bst
