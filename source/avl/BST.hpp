#pragma once

#include <cassert>
#include <concepts>

namespace avl {

template <class T>
concept Ordered = requires(const T& lhs, const T& rhs) {
  { lhs == rhs } -> std::same_as<bool>;
  { lhs < rhs } -> std::same_as<bool>;
  { lhs <= rhs } -> std::same_as<bool>;
  { lhs > rhs } -> std::same_as<bool>;
  { lhs >= rhs } -> std::same_as<bool>;
};

template <class Node>
concept BSTNode = requires(Node* node) {
  { node->parent } -> std::convertible_to<Node*>;
  { node->left } -> std::convertible_to<Node*>;
  { node->right } -> std::convertible_to<Node*>;
  { node->key } -> std::convertible_to<typename Node::Key>;
} && Ordered<typename Node::Key>;

template <BSTNode Node>
Node* Search(Node* node, const typename Node::Key& key) {
  while (node != nullptr && key != node->key) {
    if (key < node->key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node;
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
