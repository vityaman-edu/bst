#pragma once

#include "bst/core/Tree.hpp"
#include "bst/set/Set.hpp"

namespace bst::extra {

struct TreeInfo {
  std::size_t size = 1;

  template <BSTNode Node>
  struct Update {
    static_assert(std::same_as<typename Node::ValueType, TreeInfo>);

    void operator()(Node* parent) {
      const Node* lhs = parent->Child(Side::LEFT);
      const Node* rhs = parent->Child(Side::RIGHT);

      const std::size_t lval = lhs != nullptr ? lhs->Value().size : 0;
      const std::size_t rval = rhs != nullptr ? rhs->Value().size : 0;

      parent->Value().size = 1 + lval + rval;
    }
  };
};

template <
    BSTTree Tree,
    class Update = TreeInfo::Update<typename Tree::Node>,
    class Base = set::BSTSet<Tree, Update>>
class BSTIndexedOrderedSet final : public Base {
private:
  using Node = Tree::Node;
  using K = Tree::Node::KeyType;

public:
  BSTIndexedOrderedSet() : Base(Update{}) {
  }

  [[nodiscard]] const K& At(std::size_t index) const {
    assert(!IsEmpty());
    return At(this->Root(), index);
  }

private:
  const K& At(const Node* node, std::size_t index) const {
    const Node* left = node->Child(Side::LEFT);
    const Node* right = node->Child(Side::RIGHT);

    const std::size_t left_size = left != nullptr ? left->Value().size : 0;
    if (index < left_size) {
      return At(left, index);
    }
    if (index == left_size) {
      return node->Key();
    }
    return At(right, index - left_size - 1);
  }
};

}  // namespace bst::extra