#pragma once

#include <cassert>
#include <compare>
#include <concepts>
#include <tuple>

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
std::tuple<Node*, std::weak_ordering> SearchParent(
    Node* node, const typename Node::Key& key
) {
  assert(node != nullptr);
  for (;;) {
    const auto ordering = key <=> node->key;
    if (ordering == std::weak_ordering::equivalent ||
        (ordering == std::weak_ordering::less && node->left == nullptr) ||
        (ordering == std::weak_ordering::greater && node->right == nullptr)) {
      return {node, ordering};
    }
    if (ordering == std::weak_ordering::less) {
      node = node->left;
    } else {
      node = node->right;
    }
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
Node* Min(Node* node) {
  assert(node != nullptr);
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <BSTNode Node>
Node* Max(Node* node) {
  assert(node != nullptr);
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
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
