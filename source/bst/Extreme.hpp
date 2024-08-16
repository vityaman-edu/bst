#pragma once

#include "bst/Node.hpp"
#include "bst/Side.hpp"
#include "bst/Tree.hpp"

namespace bst {

template <BSTTree Tree, BSTNode Node = typename Tree::Node>
Node* Extreme(Tree& tree, Side side, Node* node) {
  assert(node != tree.Nil());
  while (Child(side, node) != tree.Nil()) {
    node = Child(side, node);
  }
  return node;
}

template <BSTTree Tree, BSTNode Node = typename Tree::Node>
Node* Min(Tree& tree, Node* node) {
  return Extreme(tree, Side::LEFT, node);
}

template <BSTTree Tree, BSTNode Node = typename Tree::Node>
Node* Max(Tree& tree, Node* node) {
  return Extreme(tree, Side::RIGHT, node);
}

}  // namespace bst