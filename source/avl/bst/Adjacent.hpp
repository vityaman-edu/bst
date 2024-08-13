#pragma once

#include "avl/bst/Extreme.hpp"
#include "avl/bst/Node.hpp"
#include "avl/bst/Side.hpp"
#include "avl/bst/Tree.hpp"

namespace avl {

template <BSTTree Tree, BSTNode Node = typename Tree::Node>
Node* Adjacent(Tree& tree, Side side, Node* node) {
  assert(node != tree.Nil());
  if (Child(side, node) != tree.Nil()) {
    return Extreme(tree, Reversed(side), Child(side, node));
  }
  Node* ancestor = node->parent;
  while (ancestor != tree.Nil() && node == Child(side, ancestor)) {
    node = ancestor;
    ancestor = ancestor->parent;
  }
  return ancestor;
}

template <BSTTree Tree, BSTNode Node = typename Tree::Node>
Node* Successor(Tree& tree, Node* node) {
  return Adjacent(tree, Side::RIGHT, node);
}

template <BSTTree Tree, BSTNode Node = typename Tree::Node>
Node* Predecessor(Tree& tree, Node* node) {
  return Adjacent(tree, Side::LEFT, node);
}

}  // namespace avl