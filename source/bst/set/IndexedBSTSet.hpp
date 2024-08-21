#pragma once

#include "bst/core/Tree.hpp"
#include "bst/set/Set.hpp"

namespace bst::set {

struct TreeInfo {
  std::size_t size = 1;

  template <BSTNode Node>
  struct Update {
    static_assert(std::same_as<typename Node::ValueType, TreeInfo>);

    void operator()(Node* parent) {
      const Node* lhs = parent->Child(Side::LEFT);
      const Node* rhs = parent->Child(Side::RIGHT);

      std::size_t& tval = parent->Value().size;
      const std::size_t lval = lhs != nullptr ? lhs->Value().size : 0;
      const std::size_t rval = rhs != nullptr ? rhs->Value().size : 0;

      tval = 1 + lval + rval;
    }
  };
};

template <
    BSTTree Tree,
    class Update = TreeInfo::Update<typename Tree::Node>,
    class Base = BSTSet<Tree, Update>>
class IndexedBSTSet final : public Base {
private:
  using Node = Tree::Node;
  using K = Tree::Node::KeyType;

public:
  IndexedBSTSet() : Base(Update{}) {
  }

  [[nodiscard]] const K& At(std::size_t index) const {
    assert(!this->IsEmpty());
    return At(this->Root(), index);
  }

private:
  const K& At(const Node* node, std::size_t index) const {
    const Node* lhs = node->Child(Side::LEFT);
    const Node* rhs = node->Child(Side::RIGHT);

    const std::size_t lhs_size = lhs != nullptr ? lhs->Value().size : 0;

#ifndef NDEBUG
    const std::size_t rhs_size = rhs != nullptr ? rhs->Value().size : 0;
    assert(node->Value().size == 1 + lhs_size + rhs_size);
#endif

    if (index < lhs_size) {
      return At(lhs, index);
    }

    if (index == lhs_size) {
      return node->Key();
    }

    assert(rhs != nullptr);
    return At(rhs, index - lhs_size - 1);
  }
};

}  // namespace bst::set
