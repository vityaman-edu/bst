#include <gtest/gtest.h>

#include <algorithm>
#include <ranges>
#include <set>

#include "avl/bst/Example.hpp"
#include "avl/bst/Rotate.hpp"
#include "avl/bst/SimpleNode.hpp"

namespace avl::test {

namespace {

struct NodeNeighbors {
  std::size_t parent;
  std::size_t left;
  std::size_t right;

  friend bool operator==(const NodeNeighbors&, const NodeNeighbors&) = default;
  friend bool operator!=(const NodeNeighbors&, const NodeNeighbors&) = default;
};

struct NodeState {
  std::size_t number;
  NodeNeighbors neighbors;
};

using NodeTable = std::vector<NodeState>;

using Node = SimpleNode<std::size_t>;

class SampleTree {
private:
  SampleTree() = default;

public:
  void AssertFromTable(const NodeTable& table) {
    for (const auto& [number, expected] : table) {
      NodeNeighbors actual = {
          .parent = (NodeAt(number)->parent != nullptr)
                        ? NodeAt(number)->parent->key
                        : 0,
          .left = (NodeAt(number)->left != nullptr)  //
                      ? NodeAt(number)->left->key
                      : 0,
          .right = (NodeAt(number)->right != nullptr)
                       ? NodeAt(number)->right->key
                       : 0,
      };
      if (expected != actual) {
        std::stringstream message;
        message << "Assertion failed! Node #" << number;
        message << " state (parent, left, right). ";
        message << "Expected (";
        message << expected.parent << ", ";
        message << expected.left << ", ";
        message << expected.right << ").";
        message << "Got (";
        message << actual.parent << ", ";
        message << actual.left << ", ";
        message << actual.right << ").";
        throw std::runtime_error(message.str());
      }
    }
  }

  Node* NodeAt(std::size_t index) {
    return nodes_.at(index);
  }

  static SampleTree FromTable(const NodeTable& table) {
    auto numbers =
        table |
        std::views::transform([](const NodeState& row) { return row.number; }) |
        std::ranges::to<std::set>();

    auto max_number = *std::ranges::max_element(numbers);

    SampleTree tree;

    tree.nodes_.assign(max_number + 1, nullptr);

    for (const auto number : numbers) {
      tree.nodes_.at(number) = tree.bst_(number);
    }

    for (const auto& [number, neighbors] : table) {
      tree.nodes_.at(number)->parent = tree.nodes_.at(neighbors.parent);
      tree.nodes_.at(number)->left = tree.nodes_.at(neighbors.left);
      tree.nodes_.at(number)->right = tree.nodes_.at(neighbors.right);
    }

    return tree;
  }

private:
  NodeFactory<Node> bst_;
  std::vector<Node*> nodes_;
};

}  // namespace

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
  NodeTable left = {
      {9, {0, 7, 0}},
      {7, {9, 5, 8}},
      {5, {7, 4, 6}},
      {4, {5, 0, 0}},
      {6, {5, 0, 0}},
      {8, {7, 0, 0}},
  };

  NodeTable right = {
      {9, {0, 5, 0}},
      {5, {9, 4, 7}},
      {4, {5, 0, 0}},
      {7, {5, 6, 8}},
      {6, {7, 0, 0}},
      {8, {7, 0, 0}},
  };

  auto tree = SampleTree::FromTable(right);

  // Roundtrip
  Rotate(Side::LEFT, tree.NodeAt(5));
  Rotate(Side::RIGHT, tree.NodeAt(7));

  Rotate(Side::LEFT, tree.NodeAt(5));

  tree.AssertFromTable(left);
}

}  // namespace avl::test