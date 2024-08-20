#pragma once

#include <utility>

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst {

template <WeaklyOrdered K, class Node>
struct TemplateNode {
public:
  using KeyType = K;

  TemplateNode() = default;

  explicit TemplateNode(KeyType key) : key_(std::move(key)) {
  }

  const KeyType& Key() const {
    return key_;
  }

  auto* Parent(this auto& self) {
    return self.parent_;
  }

  auto* Child(this auto& self, Side side) {
    switch (side) {
      case Side::LEFT:
        return self.left_;
      case Side::RIGHT:
        return self.right_;
    }
    std::unreachable();
  }

  void SetParent(Node* parent) {
    parent_ = parent;
  }

  void SetChild(Side side, Node* child) {
    switch (side) {
      case Side::LEFT: {
        left_ = child;
      } break;
      case Side::RIGHT: {
        right_ = child;
      } break;
    }
  }

private:
  KeyType key_;
  Node* parent_ = nullptr;
  Node* left_ = nullptr;
  Node* right_ = nullptr;
};

}  // namespace bst