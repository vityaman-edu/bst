#include <gtest/gtest.h>

#include <array>

#include "avl/BST.hpp"
#include "avl/test/bst/Example.hpp"

namespace avl::test {

////////////////////////////////////
//          9               9     //
//         /               /      //
//        7    left       5       //
//       /\    <----     /\       //
//      5 8             4 7       //
//     /\      ---->     /\       //
//    4 6      right    6 8       //
////////////////////////////////////
// Cormen, Introduction to Algorithms
// Chapter 13, Red-Black Trees, p. 336

TEST(Rotate, LeftRight) {
  using ParentLeftRight = std::tuple<std::size_t, std::size_t, std::size_t>;
  using NodeState = std::tuple<std::size_t, ParentLeftRight>;

  Nodes bst;
  Node* root = bst(9, bst(5, bst(4), bst(7, bst(6), bst(8))));

  std::vector<Node*> node;
  node.reserve(10);
  for (Node::Key i = 0; i < 10; ++i) {
    node.emplace_back(Search(root, i));
  }

  // Roundtrip
  Rotate(Side::LEFT, node[5]);
  Rotate(Side::RIGHT, node[7]);

  Rotate(Side::LEFT, node[5]);

  std::vector<NodeState> tests = {
      {9, {0, 7, 0}},
      {7, {9, 5, 8}},
      {5, {7, 4, 6}},
      {4, {5, 0, 0}},
      {6, {5, 0, 0}},
      {8, {7, 0, 0}},
  };

  for (const auto& expected : tests) {
    const auto number = std::get<0>(expected);
    NodeState actual = {
        number,
        {
            (node[number]->parent != nullptr) ? node[number]->parent->key : 0,
            (node[number]->left != nullptr) ? node[number]->left->key : 0,
            (node[number]->right != nullptr) ? node[number]->right->key : 0,
        }
    };
    ASSERT_EQ(expected, actual);
  }
}

}  // namespace avl::test