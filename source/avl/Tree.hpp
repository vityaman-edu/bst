#pragma once

#include <cassert>
#include <cmath>
#include <compare>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ostream>

#include "avl/Bias.hpp"
#include "avl/Node.hpp"
#include "avl/bst/Node.hpp"
#include "avl/bst/Print.hpp"
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
    assert(Root()->parent == Nil());

    std::cerr << "On insertion of " << node->key << std::endl;
    Print();

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

    std::cerr << "After insertion of " << node->key << std::endl;
    Print();

    assert(Height(Root()) != 0);

    return true;
  }

  void Remove(Node* node) {
    assert(node != Nil());
    assert(Root()->parent == Nil());

    std::cerr << "On removal of " << node->key << std::endl;
    Print();

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

    std::cerr << "After removal relink" << std::endl;
    Print();

    if (shrinked.node != Nil()) {
      OnRemoveFixup(shrinked.node, shrinked.side);
    }

    std::cerr << "After removal of " << node->key << std::endl;
    Print();

    assert(Height(Root()) >= 0);

    Reset(node);
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

    std::cerr << "On " << side << " InsertFixup of " << parent->key << std::endl;

    std::cerr << "Bias of " << parent->key << " is " << parent->bias << std::endl;

    parent->bias += BiasOf(side);
    if (parent->bias == Bias::NONE) {
      return;
    }

    std::cerr << "Bias of " << parent->key << " is " << parent->bias << std::endl;

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

    std::cerr << "On " << side << " Child Growth of " << parent->key << std::endl;

    if (parent->bias != BiasOf(side)) {
      parent->bias += BiasOf(side);
      std::cerr << "New bias is " << parent->bias << std::endl;
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
      std::cerr << prev->key << " -> " << next->key << std::endl;
      Print();
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

    std::cerr << "On " << side << " Child Shrinked of " << parent->key << " with bias "
              << parent->bias << std::endl;

    if (parent->bias != BiasOf(Reversed(side))) {
      parent->bias += BiasOf(Reversed(side));
      std::cerr << "New bias is " << parent->bias << std::endl;
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

  std::int64_t Height(Node* node) {
    if (node == Nil()) {
      return 0;
    }
    auto lhs = Height(Child(Side::LEFT, node));
    auto rhs = Height(Child(Side::RIGHT, node));
    if (std::abs(lhs - rhs) > 1) {
      std::cerr << "At node " << node->key << std::endl;
      std::cerr << "lhs height " << lhs << std::endl;
      std::cerr << "rhs height " << rhs << std::endl;
      std::unreachable();
    }
    return std::max(lhs, rhs) + 1;
  }

  void Print() {
    avl::Print(std::cerr, *this, [&](auto& out, Node* node) {
      out << node->key << " " << node->bias << "";
    });
  }

  void Reset(Node* node) {
    node->left = Nil();
    node->right = Nil();
    node->parent = Nil();
  }

  Node nil_ = {};
};

}  // namespace avl