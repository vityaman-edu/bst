#pragma once

#include <compare>

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst {

template <ReadonlyBSTNode Node>
Node* LowerBound(Node* root, const typename Node::KeyType& key) {
  Node* bound = nullptr;
  while (root != nullptr) {
    const auto ordering = root->Key() <=> key;
    if (ordering == std::weak_ordering::less) {
      root = root->Child(Side::RIGHT);
    } else {
      bound = root;
      root = root->Child(Side::LEFT);
    }
  }
  return bound;
}

template <ReadonlyBSTNode Node>
Node* UpperBound(Node* root, const typename Node::KeyType& key) {
  Node* bound = nullptr;
  while (root != nullptr) {
    const auto ordering = root->Key() <=> key;
    if (ordering == std::weak_ordering::greater) {
      bound = root;
      root = root->Child(Side::LEFT);
    } else {
      root = root->Child(Side::RIGHT);
    }
  }
  return bound;
}

}  // namespace bst