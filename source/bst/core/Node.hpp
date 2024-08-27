#pragma once

#include <concepts>
#include <initializer_list>

#include "bst/core/Side.hpp"
#include "bst/core/WeaklyOrdered.hpp"
#include "bst/support/Unreachable.hpp"

namespace bst {

template <class Node>
concept ReadonlyBSTNode = requires(const Node* readonly, Side side) {
  { readonly->Key() } -> std::convertible_to<const typename Node::KeyType&>;
  { readonly->Value() } -> std::convertible_to<const typename Node::ValueType&>;
  { readonly->Parent() } -> std::convertible_to<const Node*>;
  { readonly->Child(side) } -> std::convertible_to<const Node*>;
} && WeaklyOrdered<typename Node::KeyType>;

template <class Node>
concept BSTNode = requires(Node* writable, const Node* readonly, Side side) {
  { writable->Value() } -> std::convertible_to<typename Node::ValueType&>;
  { writable->SetParent(writable) } -> std::same_as<void>;
  { writable->Parent() } -> std::convertible_to<Node*>;
  { writable->SetChild(side, writable) } -> std::same_as<void>;
  { writable->Child(side) } -> std::convertible_to<Node*>;
} && ReadonlyBSTNode<Node>;

template <BSTNode Node>
void LinkChild(Node* node, Side side, Node* child) {
  node->SetChild(side, child);
  if (child != nullptr) {
    child->SetParent(node);
  }
}

template <BSTNode Node>
Side SideOf(const Node* node) {
  for (Side side : {Side::LEFT, Side::RIGHT}) {
    if (node->Parent()->Child(side) == node) {
      return side;
    }
  }
  Unreachable();
}

}  // namespace bst