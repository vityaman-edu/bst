#include <gtest/gtest.h>

#include <algorithm>
#include <ranges>
#include <set>

#include "bst/Example.hpp"
#include "bst/algo/Rotate.hpp"
#include "bst/naive/Node.hpp"

namespace bst {

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

using Node = NaiveNode<std::size_t>;

class SampleTree {
private:
  SampleTree() = default;

public:
  void AssertFromTable(const NodeTable& table) {
    for (const auto& [number, expected] : table) {
      NodeNeighbors actual = {
          .parent = (NodeAt(number)->parent != nullptr) ? NodeAt(number)->parent->key : 0,
          .left = (NodeAt(number)->left != nullptr)  //
                      ? NodeAt(number)->left->key
                      : 0,
          .right = (NodeAt(number)->right != nullptr) ? NodeAt(number)->right->key : 0,
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
    auto numbers = table | std::views::transform([](const NodeState& row) { return row.number; }) |
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
  NaiveNodeFactory<Node::Key> bst_;
  std::vector<Node*> nodes_;
};

}  // namespace

namespace {

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

const NodeTable RotatedLeft  // NOLINT
    {
        {9, {0, 7, 0}},
        {7, {9, 5, 8}},
        {5, {7, 4, 6}},
        {4, {5, 0, 0}},
        {6, {5, 0, 0}},
        {8, {7, 0, 0}},
};

const NodeTable RotatedRight  // NOLINT
    {
        {9, {0, 5, 0}},
        {5, {9, 4, 7}},
        {4, {5, 0, 0}},
        {7, {5, 6, 8}},
        {6, {7, 0, 0}},
        {8, {7, 0, 0}},
};

}  // namespace

TEST(Rotate, Left) {
  auto tree = SampleTree::FromTable(RotatedRight);
  tree.AssertFromTable(RotatedRight);

  Rotate(Side::LEFT, tree.NodeAt(5));
  tree.AssertFromTable(RotatedLeft);
}

TEST(Rotate, Right) {
  auto tree = SampleTree::FromTable(RotatedLeft);
  tree.AssertFromTable(RotatedLeft);

  Rotate(Side::RIGHT, tree.NodeAt(7));
  tree.AssertFromTable(RotatedRight);
}

TEST(Rotate, LeftRight) {
  auto tree = SampleTree::FromTable(RotatedRight);
  tree.AssertFromTable(RotatedRight);

  Rotate(Side::LEFT, tree.NodeAt(5));
  tree.AssertFromTable(RotatedLeft);

  Rotate(Side::RIGHT, tree.NodeAt(7));
  tree.AssertFromTable(RotatedRight);

  Rotate(Side::LEFT, tree.NodeAt(5));
  tree.AssertFromTable(RotatedLeft);
}

namespace {

/**
 *          9             9            9
 *         /             /            /
 *        7             7            5
 *       / \           / \        /    \
 *      3  8   =>     5  8  =>   3      7
 *     / \           / \        / \    / \
 *    2   5         3   6      2   4  6   8
 *       / \       / \
 *      4   6     2   4
 */

const NodeTable LRStage0  // NOLINT
    {
        {9, {0, 7, 0}},
        {7, {9, 3, 8}},
        {3, {7, 2, 5}},
        {8, {7, 0, 0}},
        {2, {3, 0, 0}},
        {5, {3, 4, 6}},
        {4, {5, 0, 0}},
        {6, {5, 0, 0}},
};

const NodeTable LRStage1  // NOLINT
    {
        {9, {0, 7, 0}},
        {7, {9, 5, 8}},
        {5, {7, 3, 6}},
        {8, {7, 0, 0}},
        {3, {5, 2, 4}},
        {6, {5, 0, 0}},
        {2, {3, 0, 0}},
        {4, {3, 0, 0}},
};

const NodeTable LRStage2  // NOLINT
    {
        {9, {0, 5, 0}},
        {5, {9, 3, 7}},
        {3, {5, 2, 4}},
        {7, {5, 6, 8}},
        {2, {3, 0, 0}},
        {4, {3, 0, 0}},
        {6, {7, 0, 0}},
        {8, {7, 0, 0}},
};

}  // namespace

TEST(Rotate, LeftThenRight) {
  auto tree = SampleTree::FromTable(LRStage0);

  Rotate(Side::LEFT, tree.NodeAt(3));
  tree.AssertFromTable(LRStage1);

  Rotate(Side::RIGHT, tree.NodeAt(7));
  tree.AssertFromTable(LRStage2);
}

TEST(DoubleRotate, Right) {
  auto tree = SampleTree::FromTable(LRStage0);

  DoubleRotate(Side::RIGHT, tree.NodeAt(7));
  tree.AssertFromTable(LRStage2);
}

namespace {

/**
 *        9           9                9
 *       /           /                /
 *      3           3                5
 *     / \         / \            /    \
 *    2   7   =>  2   5    =>    3      7
 *       / \         / \        / \    / \
 *      5   8       4   7      2   4  6   8
 *     / \             / \
 *    4   6           6   8
 */

const NodeTable RLStage0  // NOLINT
    {
        {9, {0, 3, 0}},
        {3, {9, 2, 7}},
        {2, {3, 0, 0}},
        {7, {3, 5, 8}},
        {5, {7, 4, 6}},
        {8, {7, 0, 0}},
        {4, {5, 0, 0}},
        {6, {5, 0, 0}},
};

const NodeTable RLStage1  // NOLINT
    {
        {9, {0, 3, 0}},
        {3, {9, 2, 5}},
        {2, {3, 0, 0}},
        {5, {3, 4, 7}},
        {4, {5, 0, 0}},
        {7, {5, 6, 8}},
        {6, {7, 0, 0}},
        {8, {7, 0, 0}},
};

const NodeTable RLStage2 = LRStage2;  // NOLINT

}  // namespace

TEST(Rotate, RightThenLeft) {
  auto tree = SampleTree::FromTable(RLStage0);

  Rotate(Side::RIGHT, tree.NodeAt(7));
  tree.AssertFromTable(RLStage1);

  Rotate(Side::LEFT, tree.NodeAt(3));
  tree.AssertFromTable(RLStage2);
}

TEST(DoubleRotate, Left) {
  auto tree = SampleTree::FromTable(RLStage0);

  DoubleRotate(Side::LEFT, tree.NodeAt(3));
  tree.AssertFromTable(RLStage2);
}

}  // namespace bst