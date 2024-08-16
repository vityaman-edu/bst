#pragma once

#include <concepts>

#include "bst/Node.hpp"

namespace bst {

template <class Tree>
concept BSTTree = requires(Tree tree, Tree::Node* node) {
  { tree.Root() } -> std::convertible_to<typename Tree::Node*>;
  { tree.Insert(node) } -> std::convertible_to<bool>;
  { tree.Remove(node) };
} && std::default_initializable<Tree> && std::movable<Tree> && BSTNode<typename Tree::Node>;

}  // namespace bst