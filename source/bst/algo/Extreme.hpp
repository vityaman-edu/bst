#pragma once

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst {

template <ReadonlyBSTNode Node>
Node* Extreme(Side side, Node* node) {
  while (node->Child(side) != nullptr) {
    node = node->Child(side);
  }
  return node;
}

template <ReadonlyBSTNode Node>
Node* Min(Node* node) {
  return Extreme(Side::LEFT, node);
}

template <ReadonlyBSTNode Node>
Node* Max(Node* node) {
  return Extreme(Side::RIGHT, node);
}

}  // namespace bst