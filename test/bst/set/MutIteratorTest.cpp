#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bst/Example.hpp"
#include "bst/algo/Extreme.hpp"
#include "bst/core/Node.hpp"
#include "bst/naive/Node.hpp"
#include "bst/naive/Tree.hpp"
#include "bst/set/ConstIterator.hpp"

namespace bst::set {

template <BSTNode Node>
class BSTKeyRange {
public:
  explicit BSTKeyRange(Node* node) : node_(node) {
  }

  ConstIterator<Node> begin() {
    if (node_ == nullptr) {
      return end();
    }
    return ConstIterator<Node>(Min(node_));
  }

  ConstIterator<Node> end() {
    return ConstIterator<Node>();
  }

private:
  Node* node_;
};

TEST(ConstIterator, Empty) {
  NaiveTree<int> tree;
  auto range = BSTKeyRange<NaiveNode<int>>(tree.Root());
  ASSERT_EQ(range.begin(), range.end());
}

TEST(ConstIterator, Forward) {
  using Tree = NaiveTree<int>;
  using Node = Tree::Node;

  static_assert(std::bidirectional_iterator<ConstIterator<Node>>);
  static_assert(std::ranges::bidirectional_range<BSTKeyRange<Node>>);

  auto [nodes, tree] = Example<int>();

  std::vector<Node::KeyType> keys;
  for (const auto& key : BSTKeyRange(tree.Root())) {
    keys.emplace_back(key);
  }

  ASSERT_THAT(keys, testing::ElementsAreArray({1, 3, 4, 6, 7, 8, 10, 13, 14}));
  ASSERT_TRUE(std::ranges::is_sorted(BSTKeyRange(tree.Root())));
}

}  // namespace bst::set