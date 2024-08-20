#pragma once

#include "bst/algo/Extreme.hpp"
#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst {

template <ReadonlyBSTNode Node>
Node* Adjacent(Side side, Node* node) {
  assert(node != nullptr);
  if (node->Child(side) != nullptr) {
    return Extreme(-side, node->Child(side));
  }
  Node* ancestor = node->Parent();
  while (ancestor != nullptr && node == ancestor->Child(side)) {
    node = ancestor;
    ancestor = ancestor->Parent();
  }
  return ancestor;
}

template <ReadonlyBSTNode Node>
Node* Successor(Node* node) {
  return Adjacent(Side::RIGHT, node);
}

template <ReadonlyBSTNode Node>
Node* Predecessor(Node* node) {
  return Adjacent(Side::LEFT, node);
}

}  // namespace bst