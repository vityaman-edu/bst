#pragma once

#include <compare>
#include <tuple>

#include "avl/bst/Node.hpp"

namespace avl {

template <BSTNode Node>
std::tuple<Node*, std::weak_ordering> SearchParent(
    Node* node, const typename Node::Key& key
) {
  assert(node != nullptr);
  for (;;) {
    const auto ordering = key <=> node->key;
    if (ordering == std::weak_ordering::equivalent ||
        Child(SideOf(ordering), node) == nullptr) {
      return {node, ordering};
    }
    node = Child(SideOf(ordering), node);
  }
}

template <BSTNode Node>
Node* Search(Node* node, const typename Node::Key& key) {
  auto [parent, ordering] = SearchParent(node, key);
  if (ordering == std::weak_ordering::equivalent) {
    return parent;
  }
  return nullptr;
}

}  // namespace avl