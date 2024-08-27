#pragma once

#include <concepts>

#include "bst/core/Node.hpp"
#include "bst/core/UpdateCallback.hpp"

namespace bst {

template <class Tree>
concept BSTTree =
    requires(Tree writable, const Tree readonly, Tree::Node* node) {
      { writable.Root() } -> std::convertible_to<typename Tree::Node*>;
      { writable.Insert(node) } -> std::convertible_to<bool>;
      { writable.Remove(node) };
      { writable.Root() } -> std::convertible_to<typename Tree::Node*>;
      { readonly.Root() } -> std::convertible_to<const typename Tree::Node*>;
    } && std::default_initializable<Tree> && std::movable<Tree> &&
    UpdateCallback<typename Tree::UpdateCallback, typename Tree::Node::ValueType> &&
    std::default_initializable<typename Tree::UpdateCallback> && BSTNode<typename Tree::Node>;

}  // namespace bst