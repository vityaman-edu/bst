#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "avl/BST.hpp"
#include "avl/MutIterator.hpp"
#include "avl/test/bst/Example.hpp"

namespace avl::test {

template <BSTNode Node>
class BSTKeyRange {
public:
  explicit BSTKeyRange(Node* root) : root_(root) {
  }

  MutIterator<Node> begin() {
    return MutIterator<Node>(Min(root_));
  }

  MutIterator<Node> end() {
    return MutIterator<Node>(nullptr);
  }

private:
  Node* root_;
};

TEST(MutIterator, Forward) {
  auto [nodes, root] = Example();

  std::vector<Node::Key> keys;
  for (const auto& key : BSTKeyRange(root)) {
    keys.emplace_back(key);
  }

  ASSERT_THAT(keys, testing::ElementsAreArray({1, 3, 4, 6, 7, 8, 10, 13, 14}));
}

}  // namespace avl::test