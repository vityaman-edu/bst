#pragma once

#include <compare>
#include <concepts>
#include <utility>

#include "bst/core/Side.hpp"

namespace bst {

template <class T>
concept WeaklyOrdered = requires(const T& lhs, const T& rhs) {
  { lhs <=> rhs } -> std::convertible_to<std::weak_ordering>;
};

template <class Node>
concept ReadonlyBSTNode = requires(const Node* readonly, Side side) {
  { readonly->Key() } -> std::convertible_to<const typename Node::KeyType&>;
  { readonly->Parent() } -> std::convertible_to<const Node*>;
  { readonly->Child(side) } -> std::convertible_to<const Node*>;
} && WeaklyOrdered<typename Node::KeyType>;

template <class Node>
concept BSTNode = requires(Node* writable, const Node* readonly, Side side) {
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
  std::unreachable();
}

}  // namespace bst