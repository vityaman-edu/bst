#pragma once

#include <cassert>
#include <cmath>
#include <compare>
#include <cstdint>
#include <cstdlib>
#include <tuple>

#include "avl/Bias.hpp"
#include "avl/Node.hpp"
#include "avl/bst/Node.hpp"
#include "avl/bst/Rotate.hpp"
#include "avl/bst/Side.hpp"

// #define DEBUG
#ifdef DEBUG

#include <iostream>

#include "avl/bst/Print.hpp"

#endif

namespace avl {

template <WeaklyOrdered K>
struct AVLTree {
public:
  using Node = AVLNode<K>;

  AVLTree() {
    Reset(Nil());
  }

  bool Insert(Node* node) {
#ifdef DEBUG
    std::cerr << "Inserting " << *node << std::endl;
#endif

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
#ifdef DEBUG
    std::cerr << "Removing " << *node << std::endl;
#endif

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

#ifdef DEBUG
    std::cerr << "After " << *node << " removal" << std::endl;
    Print(std::cerr, *this);
#endif

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
    while (parent != Nil()) {
      auto [next_parent, next_side] = OnChildShrinkedFixup(side, parent);
      parent = next_parent;
      side = next_side;
    }
  }

  std::tuple<Node*, Side> OnChildShrinkedFixup(Side side, Node* parent) {
    assert(parent != Nil());

#ifdef DEBUG
    std::cerr << "Shrinked " << side << " child of " << *parent << " <- " << *Child(side, parent)
              << std::endl;
#endif

    if (parent->bias != BiasOf(Reversed(side))) {
#ifdef DEBUG
      std::cerr << "Case Simple. Parent bias changed " << parent->bias << " -> "
                << parent->bias + Bias(Reversed(side)) << std::endl;
#endif
      parent->bias += BiasOf(Reversed(side));
      if (parent->bias != Bias::NONE) {
        return {Nil(), Side::LEFT};
      }
      return {parent->parent, SideOf(parent)};
    }

    auto* node = Child(Reversed(side), parent);
    assert(node != Nil());

    if (node->bias != BiasOf(side)) {
#ifdef DEBUG
      std::cerr << "Case Rotate. " << std::endl;
#endif
      Rotate(side, parent);
      if (node->bias == Bias::NONE) {
        node->bias += BiasOf(side);
        return {Nil(), Side::LEFT};
      }
      parent->bias += BiasOf(side);
      node->bias += BiasOf(side);
      return {node->parent, SideOf(node)};
    }

#ifdef DEBUG
    std::cerr << "Case DoubleRotate. " << std::endl;
#endif
    auto lifted = BiasedDoubleRotate(side, parent);
#ifdef DEBUG
    std::cerr << "Lifed " << *lifted << ", " << "parent " << *lifted->parent << std::endl;
#endif
    return {lifted->parent, SideOf(lifted)};
  }

  Node* BiasedDoubleRotate(Side side, Node* upper) {
    Node* midle = Child(Reversed(side), upper);
    Node* lower = Child(side, midle);
#ifdef DEBUG
    std::cerr << "DoubleRotate " << *upper << ", " << *midle << ", " << *lower << std::endl;
#endif

    upper->bias = ((BiasOf(Reversed(side)) == lower->bias) ? (-lower->bias) : (Bias::NONE));
    midle->bias = ((BiasOf(side) == lower->bias) ? (-lower->bias) : (Bias::NONE));
    lower->bias = Bias::NONE;

    DoubleRotate(side, upper);

    return lower;
  }

  void Reset(Node* node) {
    node->left = Nil();
    node->right = Nil();
    node->parent = Nil();
  }

  void EnsureSanity() {
#ifdef DEBUG
    std::cerr << "Ensuring sanity..." << std::endl;
    Print(std::cerr, *this);
#endif

    assert(Nil()->left == Root());
    assert(Nil()->right == Nil());
    assert(Root()->parent == Nil());
    assert(Height(Root()) >= 0);
  }

  std::int64_t Height(Node* node) {
    if (node == Nil()) {
      return 0;
    }

    assert(node->parent == Nil() || node->parent != node->left);
    assert(node->parent == Nil() || node->parent != node->right);
    assert(node != node->left);
    assert(node != node->right);
    assert(node != node->parent);

    auto lhs = Child(Side::LEFT, node);
    auto rhs = Child(Side::RIGHT, node);

    assert(lhs == Nil() || lhs->parent == node);
    assert(rhs == Nil() || rhs->parent == node);

    auto lheight = Height(lhs);
    auto rheight = Height(rhs);

    assert(node->bias == BiasOf(lheight <=> rheight));
    assert(std::abs(lheight - rheight) <= 1);

    return std::max(lheight, rheight) + 1;
  }

  Node nil_ = {};
};

}  // namespace avl