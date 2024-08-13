#include <gtest/gtest.h>

#include "avl/bst/Example.hpp"
#include "avl/bst/Search.hpp"
#include "avl/bst/SimpleNode.hpp"
#include "avl/bst/SimpleTree.hpp"

namespace avl::test {

TEST(BSTSearch, Simple) {
  SimpleNodeFactory<int> bst;

  SimpleTree<int> tree;
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
  SimpleTree<int> tree;
  SimpleNode<int> node = {.key = 5};
  ASSERT_EQ(Search(tree, &node, 5), &node);
  ASSERT_EQ(Search(tree, &node, 0), nullptr);
  ASSERT_EQ(Search(tree, &node, 10), nullptr);
}

}  // namespace avl::test
