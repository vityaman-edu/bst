#pragma once

#include <cassert>
#include <compare>

#include "avl/Bias.hpp"
#include "avl/Node.hpp"
#include "avl/bst/Node.hpp"
#include "avl/bst/Rotate.hpp"
#include "avl/bst/Side.hpp"

namespace avl {

template <WeaklyOrdered K>
struct AVLTree {
public:
  using Node = AVLNode<K>;

  AVLTree() {
    Reset(Nil());
  }

  bool Insert(Node* node) {
    Reset(node);

    if (Root() == Nil()) {
      LinkChild(Nil(), Side::LEFT, node);
      return true;
    }

    auto [parent, order] = SearchParent(*this, Root(), node->key);
    if (order == std::weak_ordering::equivalent) {
      return false;
    }

    auto side = SideOf(order);
    LinkChild(parent, side, node);
    OnInsertFixup(parent, side);
    return true;
  }

  Node* Nil() {
    return &nil_;
  }

  Node* Root() {
    return nil_.left;
  }

private:
  void OnInsertFixup(Node* parent, Side side) {
    parent->bias += BiasOf(side);
    if (parent->bias == Bias::NONE || parent == Root()) {
      return;
    }

    for (                                             //
        Node *prev = parent, *next = parent->parent;  //
        next != Nil();                                //
        prev = next, next = next->parent              //
    ) {
      OnChildGrowthFixup(SideOf(prev), next);
      if (next->bias == Bias::NONE) {
        break;
      }
    }
  }

  void OnChildGrowthFixup(Side side, Node* parent) {
    if (BiasOf(side) != parent->bias) {
      parent->bias += BiasOf(side);
    } else {
      parent->bias = Bias::NONE;
      Child(side, parent)->bias = Bias::NONE;
      Rotate(Reversed(side), parent);
    }
  }

  void Reset(Node* node) {
    node->left = Nil();
    node->right = Nil();
    node->parent = Nil();
  }

  Node nil_ = {};
};

}  // namespace avl