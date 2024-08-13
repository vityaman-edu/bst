#pragma once

#include <optional>

#include "avl/bst/Adjacent.hpp"
#include "avl/bst/Node.hpp"
#include "avl/bst/Search.hpp"
#include "avl/bst/Side.hpp"
#include "avl/bst/SimpleNode.hpp"

namespace avl::test {

template <class K>
class SimpleTree {
public:
  using Node = SimpleNode<K>;

  SimpleTree() = default;

  explicit SimpleTree(Node* root) : root_(root) {
    assert(root != nullptr);
  }

  bool Insert(Node* node) {
    Reset(node);

    if (root_ == Nil()) {
      root_ = node;
      return true;
    }

    auto [parent, order] = SearchParent(*this, root_, node->key);
    if (order == std::weak_ordering::equivalent) {
      return false;
    }

    LinkChild(parent, SideOf(order), node);
    return true;
  }

  void Remove(Node* node) {
    assert(node != Nil());

    std::optional<Node> dummy = std::nullopt;

    if (node->parent == Nil()) {
      dummy = Node();
      LinkChild(&dummy.value(), Side::LEFT, node);
    }

    if (node->left == Nil() && node->right == Nil()) {
      Child(SideOf(node), node->parent) = Nil();
    } else if (node->left == Nil() || node->right == Nil()) {
      Node* child = node->left == Nil() ? node->right : node->left;
      LinkChild(node->parent, SideOf(node), child);
    } else {
      Node* successor = Successor(*this, node);
      LinkChild(successor->parent, SideOf(successor), successor->right);
      LinkChild(node->parent, SideOf(node), successor);
      for (auto side : {Side::LEFT, Side::RIGHT}) {
        LinkChild(successor, side, Child(side, node));
      }
    }

    if (dummy != std::nullopt) {
      root_ = dummy->left;
      if (root_ != nullptr) {
        root_->parent = Nil();
      }
    }
  }

  Node* Nil() {
    return nullptr;
  }

  Node* Root() {
    return root_;
  }

private:
  void Reset(Node* node) {
    node->left = Nil();
    node->right = Nil();
    node->parent = Nil();
  }

  Node* root_ = nullptr;
};

}  // namespace avl::test