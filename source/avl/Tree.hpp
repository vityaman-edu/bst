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

  bool Insert(Node* node) {
    if (root_ == nullptr) {
      root_ = node;
      return true;
    }

    auto [parent, order] = SearchParent(root_, node->key);
    if (order == std::weak_ordering::equivalent) {
      return false;
    }

    auto side = SideOf(order);
    LinkChild(parent, side, node);
    OnInsertFixup(parent, side);
    return true;
  }

  Node* Root() {
    return root_;
  }

private:
  void OnInsertFixup(Node* parent, Side side) {
    parent->bias += BiasOf(side);
    if (parent->bias == Bias::NONE || parent == root_) {
      return;
    }

    for (                                             //
        Node *prev = parent, *next = parent->parent;  //
        next != root_;                                //
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

  Node* root_ = nullptr;
};

}  // namespace avl