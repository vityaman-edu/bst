#pragma once

#include "avl/BST.hpp"

namespace avl {

template <BSTNode Node>
class MutIterator {
public:
  explicit MutIterator(Node* node) : node_(node) {
  }

  Node::Key& operator*() {
    return node_->key;
  }

  MutIterator& operator++() {
    node_ = Successor(node_);
    return *this;
  }

  const MutIterator operator++(int) {  // NOLINT
    auto prev = *this;
    ++*this;
    return prev;
  }

  MutIterator& operator--() {
    node_ = Predecessor(node_);
    return *this;
  }

  const MutIterator operator--(int) {  // NOLINT
    auto next = *this;
    --*this;
    return next;
  }

  bool operator==(const MutIterator& rhs) const {
    return node_ == rhs.node_;
  }

  bool operator!=(const MutIterator& rhs) const = default;

private:
  Node* node_;
};

}  // namespace avl