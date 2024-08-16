#pragma once

#include "bst/Extreme.hpp"
#include "bst/Node.hpp"
#include "bst/Side.hpp"

namespace bst {

template <BSTNode Node>
Node* Adjacent(Side side, Node* node) {
  assert(node != nullptr);
  if (Child(side, node) != nullptr) {
    return Extreme(Reversed(side), Child(side, node));
  }
  Node* ancestor = node->parent;
  while (ancestor != nullptr && node == Child(side, ancestor)) {
    node = ancestor;
    ancestor = ancestor->parent;
  }
  return ancestor;
}

template <BSTNode Node>
Node* Successor(Node* node) {
  return Adjacent(Side::RIGHT, node);
}

template <BSTNode Node>
Node* Predecessor(Node* node) {
  return Adjacent(Side::LEFT, node);
}

}  // namespace bst