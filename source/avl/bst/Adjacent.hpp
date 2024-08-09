#pragma once

#include "avl/bst/Core.hpp"
#include "avl/bst/Extreme.hpp"
#include "avl/bst/Side.hpp"

namespace avl {

template <BSTNode Node>
Node* AdjacentAt(Side side, Node* node) {
  assert(node != nullptr);
  if (Child(side, node) != nullptr) {
    return ExtremeAt(Reversed(side), Child(side, node));
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
  return AdjacentAt(Side::RIGHT, node);
}

template <BSTNode Node>
Node* Predecessor(Node* node) {
  return AdjacentAt(Side::LEFT, node);
}

}  // namespace avl