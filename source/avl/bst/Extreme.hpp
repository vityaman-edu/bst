#pragma once

#include "avl/bst/Core.hpp"
#include "avl/bst/Side.hpp"

namespace avl {

template <BSTNode Node>
Node* ExtremeAt(Side side, Node* node) {
  assert(node != nullptr);
  while (Child(side, node) != nullptr) {
    node = Child(side, node);
  }
  return node;
}

template <BSTNode Node>
Node* Min(Node* node) {
  return ExtremeAt(Side::LEFT, node);
}

template <BSTNode Node>
Node* Max(Node* node) {
  return ExtremeAt(Side::RIGHT, node);
}

}  // namespace avl