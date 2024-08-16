#pragma once

#include <cassert>
#include <iterator>

#include "bst/Adjacent.hpp"
#include "bst/Node.hpp"
#include "bst/Tree.hpp"

namespace bst {

template <BSTTree Tree, BSTNode Node = typename Tree::Node>
class MutIterator final {
public:
  using iterator_category = std::bidirectional_iterator_tag;  // NOLINT
  using value_type = Node::Key;                               // NOLINT
  using difference_type = std::ptrdiff_t;                     // NOLINT
  using pointer = Node::Key*;                                 // NOLINT
  using reference = Node::Key&;                               // NOLINT

  MutIterator() = default;

  explicit MutIterator(Tree* tree, Node* node) : tree_(tree), node_(node) {
    assert(tree != nullptr);
    assert(node != nullptr);
    assert(node != tree->Nil());
  }

  Node::Key& operator*() const {
    return node_->key;
  }

  MutIterator& operator++() {
    SetNode(Successor(*tree_, node_));
    return *this;
  }

  MutIterator operator++(int) {  // NOLINT
    auto prev = *this;
    ++*this;
    return prev;
  }

  MutIterator& operator--() {
    SetNode(Predecessor(*tree_, node_));
    return *this;
  }

  MutIterator operator--(int) {  // NOLINT
    auto next = *this;
    --*this;
    return next;
  }

  bool operator==(const MutIterator& rhs) const {
    return this->node_ == rhs.node_;
  }

  bool operator!=(const MutIterator& rhs) const {
    return !(*this == rhs);
  }

private:
  void SetNode(Node* node) {
    node_ = node != tree_->Nil() ? node : nullptr;
  }

  Tree* tree_ = nullptr;
  Node* node_ = nullptr;
};

}  // namespace bst