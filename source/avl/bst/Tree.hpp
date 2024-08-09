#pragma once

#include <concepts>

#include "avl/bst/Node.hpp"

namespace avl {

template <class Tree>
concept BSTTree = requires(Tree tree, Tree::Node* node) {
  { tree.Root() } -> std::convertible_to<typename Tree::Node*>;
  { tree.Insert(node) } -> std::convertible_to<bool>;
} && std::default_initializable<Tree> && BSTNode<typename Tree::Node>;

}  // namespace avl