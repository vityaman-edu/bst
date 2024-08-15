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
    assert(node != Nil());
    EnsureSanity();

    Reset(node);

    if (Root() == Nil()) {
      LinkChild(Nil(), Side::LEFT, node);
      EnsureSanity();
      return true;
    }

    auto [parent, order] = SearchParent(*this, Root(), node->key);
    if (order == std::weak_ordering::equivalent) {
      return false;
    }

    auto side = SideOf(order);
    LinkChild(parent, side, node);
    OnInsertFixup(parent, side);

    EnsureSanity();
    return true;
  }

  void Remove(Node* node) {
    assert(node != Nil());
    EnsureSanity();

    struct {
      Node* node;
      Side side;
    } shrinked;

    if (node->left == Nil() && node->right == Nil()) {
      shrinked = {.node = node->parent, .side = SideOf(node)};
      LinkChild(node->parent, SideOf(node), Nil());
    } else if (node->left == Nil() || node->right == Nil()) {
      shrinked = {.node = node->parent, .side = SideOf(node)};
      Node* child = node->left == Nil() ? node->right : node->left;
      LinkChild(node->parent, SideOf(node), child);
    } else {
      Node* successor = Successor(*this, node);
      shrinked = {.node = successor->parent, .side = SideOf(successor)};
      if (shrinked.node == node) {
        shrinked.node = successor;
      }
      LinkChild(successor->parent, SideOf(successor), successor->right);
      successor->bias = node->bias;
      LinkChild(node->parent, SideOf(node), successor);
      for (auto side : {Side::LEFT, Side::RIGHT}) {
        LinkChild(successor, side, Child(side, node));
      }
    }

    if (shrinked.node != Nil()) {
      OnRemoveFixup(shrinked.node, shrinked.side);
    }

    Reset(node);

    EnsureSanity();
  }

  Node* Nil() {
    return &nil_;
  }

  Node* Root() {
    return nil_.left;
  }

private:
  void OnInsertFixup(Node* parent, Side side) {
    assert(parent != Nil());

    parent->bias += BiasOf(side);
    if (parent->bias == Bias::NONE) {
      return;
    }

    for (                                             //
        Node *prev = parent, *next = parent->parent;  //
        prev != Nil() && next != Nil();               //
        prev = next, next = next->parent              //
    ) {
      if (OnChildGrowthFixup(SideOf(prev), next)) {
        break;
      }
    }
  }

  bool OnChildGrowthFixup(Side side, Node* parent) {
    assert(parent != Nil());

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
      BiasedDoubleRotate(Reversed(side), parent);
    }

    return true;
  }

  void OnRemoveFixup(Node* parent, Side side) {
    if (OnChildShrinkedFixup(side, parent)) {
      return;
    }
    for (                                             //
        Node *prev = parent, *next = parent->parent;  //
        prev != Nil() && next != Nil();               //
        prev = next, next = next->parent              //
    ) {
      auto prev_side = SideOf(next);
      auto prev_parent = next->parent;
      if (OnChildShrinkedFixup(SideOf(prev), next)) {
        break;
      }
      next = Child(prev_side, prev_parent);
    }
  }

  bool OnChildShrinkedFixup(Side side, Node* parent) {
    assert(parent != Nil());

    if (parent->bias != BiasOf(Reversed(side))) {
      parent->bias += BiasOf(Reversed(side));
      return parent->bias != Bias::NONE;
    }

    auto* node = Child(Reversed(side), parent);
    assert(node != Nil());
    if (node->bias != BiasOf(side)) {
      Rotate(side, parent);
      if (node->bias == Bias::NONE) {
        node->bias += BiasOf(side);
        return true;
      }
      parent->bias += BiasOf(side);
      node->bias += BiasOf(side);
    } else {
      BiasedDoubleRotate(side, parent);
    }

    return false;
  }

  void BiasedDoubleRotate(Side side, Node* upper) {
    Node* midle = Child(Reversed(side), upper);
    Node* lower = Child(side, midle);

    upper->bias = ((BiasOf(Reversed(side)) == lower->bias) ? (-lower->bias) : (Bias::NONE));
    midle->bias = ((BiasOf(side) == lower->bias) ? (-lower->bias) : (Bias::NONE));
    lower->bias = Bias::NONE;

    DoubleRotate(side, upper);
  }

  void Reset(Node* node) {
    node->left = Nil();
    node->right = Nil();
    node->parent = Nil();
  }

  void EnsureSanity() {
    assert(Nil()->right == Nil());
    assert(Nil()->parent == Nil());
    assert(Root()->parent == Nil());
    assert(Height(Root()) >= 0);
  }

  std::int64_t Height(Node* node) {
    if (node == Nil()) {
      return 0;
    }

    auto lhs = Height(Child(Side::LEFT, node));
    auto rhs = Height(Child(Side::RIGHT, node));

    assert(std::abs(lhs - rhs) <= 1);
    assert(node->bias == BiasOf(lhs <=> rhs));

    return std::max(lhs, rhs) + 1;
  }

  Node nil_ = {};
};

}  // namespace avl