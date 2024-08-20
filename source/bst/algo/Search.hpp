#pragma once

#include <compare>
#include <tuple>

#include "bst/core/Node.hpp"

namespace bst {

template <ReadonlyBSTNode Node>
std::tuple<Node*, std::weak_ordering> SearchParent(Node* node, const typename Node::KeyType& key) {
  for (;;) {
    const auto ordering = key <=> node->Key();
    if (ordering == std::weak_ordering::equivalent || node->Child(SideOf(ordering)) == nullptr) {
      return {node, ordering};
    }
    node = node->Child(SideOf(ordering));
  }
}

template <ReadonlyBSTNode Node>
Node* Search(Node* node, const typename Node::KeyType& key) {
  auto [parent, ordering] = SearchParent(node, key);
  if (ordering == std::weak_ordering::equivalent) {
    return parent;
  }
  return nullptr;
}

}  // namespace bst