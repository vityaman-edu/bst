#pragma once

#include <utility>

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"
#include "bst/core/WeaklyOrdered.hpp"
#include "bst/support/Unreachable.hpp"

namespace bst {

template <WeaklyOrdered K, class V, class Node>
struct TemplateNode {
public:
  using KeyType = K;
  using ValueType = V;

  TemplateNode() = default;

  explicit TemplateNode(KeyType key, ValueType value = {})
      : key_(std::move(key)), value_(std::move(value)) {
  }

  [[nodiscard]] const KeyType& Key() const {
    return key_;
  }

  [[nodiscard]] const ValueType& Value() const {
    return value_;
  }

  [[nodiscard]] ValueType& Value() {
    return value_;
  }

  [[nodiscard]] const Node* Parent() const {
    return parent_;
  }

  [[nodiscard]] Node* Parent() {
    return parent_;
  }

  [[nodiscard]] const Node* Child(Side side) const {
    switch (side) {
      case Side::LEFT:
        return left_;
      case Side::RIGHT:
        return right_;
    }
    Unreachable();
  }

  [[nodiscard]] Node* Child(Side side) {
    switch (side) {
      case Side::LEFT:
        return left_;
      case Side::RIGHT:
        return right_;
    }
    Unreachable();
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
  ValueType value_ = {};
  Node* parent_ = nullptr;
  Node* left_ = nullptr;
  Node* right_ = nullptr;
};

}  // namespace bst