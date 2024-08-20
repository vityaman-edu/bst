#pragma once

#include <cassert>
#include <iterator>

#include "bst/algo/Adjacent.hpp"
#include "bst/core/Node.hpp"

namespace bst::set {

template <BSTNode Node>
class ConstIterator final {
public:
  using iterator_category = std::bidirectional_iterator_tag;  // NOLINT
  using value_type = Node::KeyType;                           // NOLINT
  using difference_type = std::ptrdiff_t;                     // NOLINT
  using pointer = Node::KeyType*;                             // NOLINT
  using reference = Node::KeyType&;                           // NOLINT

  ConstIterator() = default;

  explicit ConstIterator(const Node* node) : node_(node) {
    assert(node != nullptr);
  }

  const Node::KeyType& operator*() const {
    return node_->Key();
  }

  ConstIterator& operator++() {
    node_ = Successor(node_);
    return *this;
  }

  ConstIterator operator++(int) {  // NOLINT
    auto prev = *this;
    ++*this;
    return prev;
  }

  ConstIterator& operator--() {
    node_ = Predecessor(node_);
    return *this;
  }

  ConstIterator operator--(int) {  // NOLINT
    auto next = *this;
    --*this;
    return next;
  }

  bool operator==(const ConstIterator& rhs) const {
    return this->node_ == rhs.node_;
  }

  bool operator!=(const ConstIterator& rhs) const {
    return !(*this == rhs);
  }

private:
  const Node* node_ = nullptr;
};

}  // namespace bst::set