#pragma once

#include "bst/core/Node.hpp"

namespace bst {

template <WeaklyOrdered K, class Node>
struct TemplateNode {
  using Key = K;

  TemplateNode() = default;

  explicit TemplateNode(Key key) : key(std::move(key)) {
  }

  Key key;
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
};

}  // namespace bst