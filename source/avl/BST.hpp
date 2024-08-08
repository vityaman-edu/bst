#pragma once

#include <cassert>
#include <compare>
#include <concepts>
#include <cstdint>
#include <tuple>
#include <utility>

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

enum class Direction : std::uint8_t { LEFT, RIGHT };

Direction DirectionOf(std::weak_ordering ordering);

template <BSTNode Node>
Node* Child(Direction direction, Node* node) {
  switch (direction) {
    case Direction::LEFT:
      return node->left;
    case Direction::RIGHT:
      return node->right;
  }
  std::unreachable();
}

template <BSTNode Node>
std::tuple<Node*, std::weak_ordering> SearchParent(
    Node* node, const typename Node::Key& key
) {
  assert(node != nullptr);
  for (;;) {
    const auto ordering = key <=> node->key;
    if (ordering == std::weak_ordering::equivalent ||
        Child(DirectionOf(ordering), node) == nullptr) {
      return {node, ordering};
    }
    node = Child(DirectionOf(ordering), node);
  }
}

template <BSTNode Node>
Node* Search(Node* node, const typename Node::Key& key) {
  auto [parent, ordering] = SearchParent(node, key);
  if (ordering == std::weak_ordering::equivalent) {
    return parent;
  }
  return nullptr;
}

template <BSTNode Node>
Node* Extreme(Direction direction, Node* node) {
  assert(node != nullptr);
  while (Child(direction, node) != nullptr) {
    node = Child(direction, node);
  }
  return node;
}

template <BSTNode Node>
Node* Min(Node* node) {
  return Extreme(Direction::LEFT, node);
}

template <BSTNode Node>
Node* Max(Node* node) {
  return Extreme(Direction::RIGHT, node);
}

template <BSTNode Node>
Node* Successor(Node* node) {
  assert(node != nullptr);
  if (node->right != nullptr) {
    return Min(node->right);
  }
  Node* ancestor = node->parent;
  while (ancestor != nullptr && node == ancestor->right) {
    node = ancestor;
    ancestor = ancestor->parent;
  }
  return ancestor;
}

template <BSTNode Node>
Node* Predecessor(Node* node) {
  assert(node != nullptr);
  if (node->left != nullptr) {
    return Max(node->left);
  }
  Node* ancestor = node->parent;
  while (ancestor != nullptr && node == ancestor->left) {
    node = ancestor;
    ancestor = ancestor->parent;
  }
  return ancestor;
}

}  // namespace avl
