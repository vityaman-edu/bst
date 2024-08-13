#pragma once

#include <compare>
#include <tuple>

#include "avl/bst/Node.hpp"
#include "avl/bst/Tree.hpp"

namespace avl {

template <BSTTree Tree, BSTNode Node = typename Tree::Node>
std::tuple<Node*, std::weak_ordering> SearchParent(
    Tree& tree, Node* node, const typename Node::Key& key
) {
  assert(node != tree.Nil());
  for (;;) {
    const auto ordering = key <=> node->key;
    if (ordering == std::weak_ordering::equivalent || Child(SideOf(ordering), node) == tree.Nil()) {
      return {node, ordering};
    }
    node = Child(SideOf(ordering), node);
  }
}

template <BSTTree Tree, BSTNode Node = typename Tree::Node>
Node* Search(Tree& tree, Node* node, const typename Node::Key& key) {
  auto [parent, ordering] = SearchParent(tree, node, key);
  if (ordering == std::weak_ordering::equivalent) {
    return parent;
  }
  return tree.Nil();
}

}  // namespace avl