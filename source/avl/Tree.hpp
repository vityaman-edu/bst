#pragma once

#include <cassert>
#include <cmath>
#include <compare>
#include <cstdint>
#include <cstdlib>

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

    assert(Height(Root()) != 0);

    return true;
  }

  void Remove(Node* /*node*/) {
    std::abort();
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
    if (parent->bias == Bias::NONE) {
      return;
    }

    for (                                             //
        Node *prev = parent, *next = parent->parent;  //
        next != Nil();                                //
        prev = next, next = next->parent              //
    ) {
      if (OnChildGrowthFixup(SideOf(prev), next)) {
        break;
      }
    }
  }

  bool OnChildGrowthFixup(Side side, Node* parent) {
    if (parent->bias != BiasOf(side)) {
      parent->bias += BiasOf(side);
      if (parent->bias != Bias::NONE) {
        return false;
      }
    } else if (Child(side, parent)->bias == BiasOf(side)) {
      parent->bias += BiasOf(Reversed(side));
      Child(side, parent)->bias += BiasOf(Reversed(side));
      Rotate(Reversed(side), parent);
    } else {
      Node* A = parent;
      Node* B = Child(side, parent);
      Node* E = Child(Reversed(side), B);

      A->bias = ((BiasOf(side) == E->bias) ? (-E->bias) : (Bias::NONE));
      B->bias = ((BiasOf(Reversed(side)) == E->bias) ? (-E->bias) : (Bias::NONE));
      E->bias = Bias::NONE;

      DoubleRotate(Reversed(side), parent);
    }

    return true;
  }

  std::int64_t Height(Node* node) {
    if (node == Nil()) {
      return 0;
    }
    auto lhs = Height(Child(Side::LEFT, node));
    auto rhs = Height(Child(Side::RIGHT, node));
    assert(std::abs(lhs - rhs) <= 1);
    return std::max(lhs, rhs) + 1;
  }

  void Reset(Node* node) {
    node->left = Nil();
    node->right = Nil();
    node->parent = Nil();
  }

  Node nil_ = {};
};

}  // namespace avl