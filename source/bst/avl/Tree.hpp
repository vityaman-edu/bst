#pragma once

#include <cassert>
#include <cmath>
#include <compare>
#include <cstdint>
#include <cstdlib>
#include <tuple>

#include "bst/Adjacent.hpp"
#include "bst/Node.hpp"
#include "bst/Rotate.hpp"
#include "bst/Search.hpp"
#include "bst/Side.hpp"
#include "bst/avl/Bias.hpp"
#include "bst/avl/Node.hpp"

namespace bst::avl {

template <WeaklyOrdered K>
struct AVLTree {
public:
  using Node = AVLNode<K>;

  AVLTree() {
    Reset(nullptr);
  }

  bool Insert(Node* node) {
    assert(node != nullptr);
    EnsureSanity();

    Reset(node);

    if (Root() == nullptr) {
      LinkChild(&nil_, Side::LEFT, node);
      EnsureSanity();
      return true;
    }

    auto [parent, order] = SearchParent(Root(), node->key);
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
    assert(node != nullptr);
    EnsureSanity();

    struct {
      Node* node;
      Side side;
    } shrinked;

    if (node->left == nullptr && node->right == nullptr) {
      shrinked = {.node = node->parent, .side = SideOf(node)};
      Child(SideOf(node), node->parent) = nullptr;
    } else if (node->left == nullptr || node->right == nullptr) {
      shrinked = {.node = node->parent, .side = SideOf(node)};
      Node* child = node->left == nullptr ? node->right : node->left;
      LinkChild(node->parent, SideOf(node), child);
    } else {
      Node* successor = Successor(node);

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

    OnRemoveFixup(shrinked.node, shrinked.side);

    Reset(node);

    EnsureSanity();
  }

  Node* Root() {
    return nil_.left;
  }

private:
  void OnInsertFixup(Node* parent, Side side) {
    assert(parent != nullptr);

    parent->bias += BiasOf(side);
    if (parent->bias == Bias::NONE) {
      return;
    }

    for (                                             //
        Node *prev = parent, *next = parent->parent;  //
        next != nullptr;                              //
        prev = next, next = next->parent              //
    ) {
      if (OnChildGrowthFixup(SideOf(prev), next)) {
        break;
      }
    }
  }

  bool OnChildGrowthFixup(Side side, Node* parent) {
    assert(parent != nullptr);

    if (parent->bias != BiasOf(side)) {
      parent->bias += BiasOf(side);
      return parent->bias == Bias::NONE;
    }

    if (Child(side, parent)->bias == BiasOf(side)) {
      parent->bias += BiasOf(Reversed(side));
      Child(side, parent)->bias += BiasOf(Reversed(side));
      Rotate(Reversed(side), parent);
    } else {
      BiasedDoubleRotate(Reversed(side), parent);
    }

    return true;
  }

  void OnRemoveFixup(Node* parent, Side side) {
    while (parent != nullptr) {
      auto next = std::tuple(parent->parent, SideOf(parent));
      if (OnChildShrinkedFixup(side, parent)) {
        break;
      }
      std::tie(parent, side) = next;
    }
  }

  bool OnChildShrinkedFixup(Side side, Node* parent) {
    assert(parent != nullptr);

    if (parent->bias != BiasOf(Reversed(side))) {
      parent->bias += BiasOf(Reversed(side));
      return parent->bias != Bias::NONE;
    }

    auto* node = Child(Reversed(side), parent);
    assert(node != nullptr);

    if (node->bias != BiasOf(side)) {
      Rotate(side, parent);
      if (node->bias != Bias::NONE) {
        parent->bias += BiasOf(side);
      }
      node->bias += BiasOf(side);
      return node->bias != Bias::NONE;
    }

    BiasedDoubleRotate(side, parent);
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
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
  }

  void EnsureSanity() {
    assert(Root()->parent == nullptr);
    assert(Height(Root()) >= 0);
  }

  std::int64_t Height(Node* node) {
    if (node == nullptr) {
      return 0;
    }

    assert(node->parent == nullptr || node->parent != node->left);
    assert(node->parent == nullptr || node->parent != node->right);
    assert(node != node->left);
    assert(node != node->right);
    assert(node != node->parent);

    auto lhs = Child(Side::LEFT, node);
    auto rhs = Child(Side::RIGHT, node);

    assert(lhs == nullptr || lhs->parent == node);
    assert(rhs == nullptr || rhs->parent == node);

    auto lheight = Height(lhs);
    auto rheight = Height(rhs);

    assert(node->bias == BiasOf(lheight <=> rheight));
    assert(std::abs(lheight - rheight) <= 1);

    return std::max(lheight, rheight) + 1;
  }

  Node nil_ = {};
};

}  // namespace bst::avl