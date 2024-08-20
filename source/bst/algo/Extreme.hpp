#pragma once

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst {

template <BSTNode Node>
Node* Extreme(Side side, Node* node) {
  assert(node != nullptr);
  while (Child(side, node) != nullptr) {
    node = Child(side, node);
  }
  return node;
}

template <BSTNode Node>
Node* Min(Node* node) {
  return Extreme(Side::LEFT, node);
}

template <BSTNode Node>
Node* Max(Node* node) {
  return Extreme(Side::RIGHT, node);
}

}  // namespace bst