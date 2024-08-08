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

enum class Side : std::uint8_t { LEFT, RIGHT };

Side Reversed(Side side);

Side SideOf(std::weak_ordering ordering);

template <BSTNode Node>
Node* Child(Side side, Node* node) {
  switch (side) {
    case Side::LEFT:
      return node->left;
    case Side::RIGHT:
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
        Child(SideOf(ordering), node) == nullptr) {
      return {node, ordering};
    }
    node = Child(SideOf(ordering), node);
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
Node* ExtremeAt(Side side, Node* node) {
  assert(node != nullptr);
  while (Child(side, node) != nullptr) {
    node = Child(side, node);
  }
  return node;
}

template <BSTNode Node>
Node* Min(Node* node) {
  return ExtremeAt(Side::LEFT, node);
}

template <BSTNode Node>
Node* Max(Node* node) {
  return ExtremeAt(Side::RIGHT, node);
}

template <BSTNode Node>
Node* AdjacentAt(Side side, Node* node) {
  assert(node != nullptr);
  if (Child(side, node) != nullptr) {
    return ExtremeAt(Reversed(side), Child(side, node));
  }
  Node* ancestor = node->parent;
  while (ancestor != nullptr && node == Child(side, ancestor)) {
    node = ancestor;
    ancestor = ancestor->parent;
  }
  return ancestor;
}

template <BSTNode Node>
Node* Successor(Node* node) {
  return AdjacentAt(Side::RIGHT, node);
}

template <BSTNode Node>
Node* Predecessor(Node* node) {
  return AdjacentAt(Side::LEFT, node);
}

}  // namespace avl
