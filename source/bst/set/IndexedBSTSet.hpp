#pragma once

#include <cassert>
#include <cstddef>

#include "bst/core/Side.hpp"
#include "bst/core/Tree.hpp"
#include "bst/set/ConstIterator.hpp"
#include "bst/set/Set.hpp"

namespace bst::set {

struct TreeInfo {
  std::size_t size = 1;

  struct Update {
    void operator()(TreeInfo* parent, const TreeInfo* lhs, const TreeInfo* rhs) {
      std::size_t& pval = parent->size;

      const std::size_t lval = lhs != nullptr ? lhs->size : 0;
      const std::size_t rval = rhs != nullptr ? rhs->size : 0;

      pval = 1 + lval + rval;
    }
  };
};

template <BSTTree Tree>
class IndexedBSTSet final : public BSTSet<Tree> {
private:
  using Node = Tree::Node;
  using K = Tree::Node::KeyType;

public:
  IndexedBSTSet() : BSTSet<Tree>({}) {
  }

  [[nodiscard]] const K& At(std::size_t index) const {
    return *IteratorAt(index);
  }

  ConstIterator<Node> IteratorAt(std::size_t index) const {
    assert(!this->IsEmpty());
    return ConstIterator<Node>(At(this->Root(), index));
  }

private:
  const Node* At(const Node* node, std::size_t index) const {
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
      return node;
    }

    assert(rhs != nullptr);
    return At(rhs, index - lhs_size - 1);
  }
};

}  // namespace bst::set
