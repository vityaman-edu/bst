#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bst/Example.hpp"
#include "bst/Extreme.hpp"
#include "bst/MutIterator.hpp"
#include "bst/naive/Node.hpp"
#include "bst/naive/Tree.hpp"

namespace bst {

template <BSTTree Tree>
class BSTKeyRange {
public:
  explicit BSTKeyRange(Tree* tree) : tree_(tree) {
  }

  MutIterator<Tree> begin() {
    if (tree_->Root() == tree_->Nil()) {
      return end();
    }
    return MutIterator<Tree>(tree_, Min(*tree_, tree_->Root()));
  }

  MutIterator<Tree> end() {
    return MutIterator<Tree>();
  }

private:
  Tree* tree_;
};

TEST(MutIterator, Empty) {
  NaiveTree<int> tree;
  auto range = BSTKeyRange<NaiveTree<int>>(&tree);
  ASSERT_EQ(range.begin(), range.end());
}

TEST(MutIterator, Forward) {
  using Tree = NaiveTree<int>;
  using Node = Tree::Node;

  static_assert(std::bidirectional_iterator<MutIterator<Tree>>);
  static_assert(std::ranges::bidirectional_range<BSTKeyRange<Tree>>);

  auto [nodes, tree] = Example<int>();

  std::vector<Node::Key> keys;
  for (const auto& key : BSTKeyRange(&tree)) {
    keys.emplace_back(key);
  }

  ASSERT_THAT(keys, testing::ElementsAreArray({1, 3, 4, 6, 7, 8, 10, 13, 14}));
  ASSERT_TRUE(std::ranges::is_sorted(BSTKeyRange(&tree)));
}

}  // namespace bst