#pragma once

#include <compare>
#include <concepts>
#include <utility>

#include "bst/Side.hpp"

namespace bst {

template <class T>
concept WeaklyOrdered = requires(const T& lhs, const T& rhs) {
  { lhs <=> rhs } -> std::convertible_to<std::weak_ordering>;
};

template <class Node>
concept BSTNode = requires(Node* node) {
  { node->parent } -> std::convertible_to<Node*>;
  { node->left } -> std::convertible_to<Node*>;
  { node->right } -> std::convertible_to<Node*>;
  { node->key } -> std::convertible_to<typename Node::Key>;
} && WeaklyOrdered<typename Node::Key>;

template <BSTNode Node>
Node*& Child(Side side, Node* node) {
  switch (side) {
    case Side::LEFT:
      return node->left;
    case Side::RIGHT:
      return node->right;
  }
  std::unreachable();
}

template <BSTNode Node>
void LinkChild(Node* node, Side side, Node* child) {
  Child(side, node) = child;
  if (child != nullptr) {
    child->parent = node;
  }
}

template <BSTNode Node>
Side SideOf(Node* node) {
  if (node->parent->left == node) {
    return Side::LEFT;
  }
  if (node->parent->right == node) {
    return Side::RIGHT;
  }
  std::unreachable();
}

}  // namespace bst