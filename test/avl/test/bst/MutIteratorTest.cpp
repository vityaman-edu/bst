#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "avl/bst/Core.hpp"
#include "avl/bst/Extreme.hpp"
#include "avl/bst/MutIterator.hpp"
#include "avl/test/bst/Example.hpp"

namespace avl::test {

template <BSTNode Node>
class BSTKeyRange {
public:
  explicit BSTKeyRange(Node* root) : root_(root) {
  }

  MutIterator<Node> begin() {
    if (root_ == nullptr) {
      return end();
    }
    return MutIterator<Node>(Min(root_));
  }

  MutIterator<Node> end() {
    return MutIterator<Node>();
  }

private:
  Node* root_;
};

TEST(MutIterator, Empty) {
  auto range = BSTKeyRange<Node>(nullptr);
  ASSERT_EQ(range.begin(), range.end());
}

TEST(MutIterator, Forward) {
  static_assert(std::bidirectional_iterator<MutIterator<Node>>);
  static_assert(std::ranges::bidirectional_range<BSTKeyRange<Node>>);

  auto [nodes, root] = Example();

  std::vector<Node::Key> keys;
  for (const auto& key : BSTKeyRange(root)) {
    keys.emplace_back(key);
  }

  ASSERT_THAT(keys, testing::ElementsAreArray({1, 3, 4, 6, 7, 8, 10, 13, 14}));
  ASSERT_TRUE(std::ranges::is_sorted(BSTKeyRange(root)));
}

}  // namespace avl::test