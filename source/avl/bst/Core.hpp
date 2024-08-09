#pragma once

#include <compare>
#include <concepts>
#include <utility>

#include "avl/bst/Side.hpp"

namespace avl {

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

}  // namespace avl