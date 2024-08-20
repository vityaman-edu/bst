#pragma once

#include <cassert>
#include <cmath>
#include <compare>
#include <cstdint>
#include <cstdlib>
#include <tuple>

#include "bst/algo/Adjacent.hpp"
#include "bst/algo/Rotate.hpp"
#include "bst/algo/Search.hpp"
#include "bst/avl/Bias.hpp"
#include "bst/avl/Node.hpp"
#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst::avl {

template <WeaklyOrdered K>
struct AVLTree {
public:
  using Node = AVLNode<K>;

  AVLTree() = default;

  AVLTree(const AVLTree&) = delete;
  AVLTree& operator=(const AVLTree&) = delete;

  AVLTree(AVLTree&& that) noexcept {
    Swap(that);
  }

  AVLTree& operator=(AVLTree&& that) noexcept {
    Swap(that);
    return *this;
  }

  ~AVLTree() = default;

  bool Insert(Node* node) {
    assert(node != nullptr);

    Before();

    Reset(node);

    if (Root() == nullptr) {
      LinkChild(Nil(), Side::LEFT, node);
      After();
      return true;
    }

    auto [parent, order] = SearchParent(Root(), node->Key());
    if (order == std::weak_ordering::equivalent) {
      return false;
    }

    auto side = SideOf(order);
    LinkChild(parent, side, node);
    OnInsertFixup(parent, side);

    After();
    return true;
  }

  void Remove(Node* node) {
    assert(node != nullptr);

    Before();

    struct {
      Node* node;
      Side side;
    } shrinked;

    if (node->Child(Side::LEFT) == nullptr && node->Child(Side::RIGHT) == nullptr) {
      shrinked = {.node = node->Parent(), .side = SideOf(node)};
      node->Parent()->SetChild(SideOf(node), nullptr);
    } else if (node->Child(Side::LEFT) == nullptr || node->Child(Side::RIGHT) == nullptr) {
      shrinked = {.node = node->Parent(), .side = SideOf(node)};
      Node* child =
          node->Child(Side::LEFT) == nullptr ? node->Child(Side::RIGHT) : node->Child(Side::LEFT);
      LinkChild(node->Parent(), SideOf(node), child);
    } else {
      Node* successor = Successor(node);

      shrinked = {.node = successor->Parent(), .side = SideOf(successor)};
      if (shrinked.node == node) {
        shrinked.node = successor;
      }

      LinkChild(successor->Parent(), SideOf(successor), successor->Child(Side::RIGHT));

      successor->bias = node->bias;
      LinkChild(node->Parent(), SideOf(node), successor);
      for (auto side : {Side::LEFT, Side::RIGHT}) {
        LinkChild(successor, side, node->Child(side));
      }
    }

    OnRemoveFixup(shrinked.node, shrinked.side);

    Reset(node);

    After();
  }

  Node* Root() const {
    return nil_.Child(Side::LEFT);
  }

private:
  void OnInsertFixup(Node* parent, Side side) {
    assert(parent != nullptr);

    parent->bias += BiasOf(side);
    if (parent->bias == Bias::NONE) {
      return;
    }

    for (                                               //
        Node *prev = parent, *next = parent->Parent();  //
        next != Nil();                                  //
        prev = next, next = next->Parent()              //
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
      return parent->bias == Bias::NONE;
    }

    if (parent->Child(side)->bias == BiasOf(side)) {
      parent->bias += BiasOf(-side);
      parent->Child(side)->bias += BiasOf(-side);
      Rotate(-side, parent);
    } else {
      BiasedDoubleRotate(-side, parent);
    }

    return true;
  }

  void OnRemoveFixup(Node* parent, Side side) {
    while (parent != Nil()) {
      auto next = std::tuple(parent->Parent(), SideOf(parent));
      if (OnChildShrinkedFixup(side, parent)) {
        break;
      }
      std::tie(parent, side) = next;
    }
  }

  bool OnChildShrinkedFixup(Side side, Node* parent) {
    assert(parent != nullptr);

    if (parent->bias != BiasOf(-side)) {
      parent->bias += BiasOf(-side);
      return parent->bias != Bias::NONE;
    }

    auto* node = parent->Child(-side);
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
    Node* midle = upper->Child(-side);
    Node* lower = midle->Child(side);

    upper->bias = ((BiasOf(-side) == lower->bias) ? (-lower->bias) : (Bias::NONE));
    midle->bias = ((BiasOf(side) == lower->bias) ? (-lower->bias) : (Bias::NONE));
    lower->bias = Bias::NONE;

    DoubleRotate(side, upper);
  }

  void Reset(Node* node) {
    node->SetChild(Side::LEFT, nullptr);
    node->SetChild(Side::RIGHT, nullptr);
    node->SetParent(nullptr);
  }

  void Before() {
    EnsureSanity();
    if (Root() != nullptr) {
      Root()->SetParent(Nil());
    }
  }

  void After() {
    if (Root() != nullptr) {
      Root()->SetParent(nullptr);
    }
    EnsureSanity();
  }

  Node* Nil() {
    return &nil_;
  }

  void Swap(AVLTree& that) {
    Side root_side = Side::LEFT;
    Node* this_root = this->nil_.Child(root_side);
    Node* that_root = that.nil_.Child(root_side);
    this->nil_.SetChild(root_side, that_root);
    that.nil_.SetChild(root_side, this_root);
  }

  void EnsureSanity() {
    assert(Root() == nullptr || Root()->Parent() == nullptr);
    assert(Height(Root()) >= 0);
  }

  std::int64_t Height(Node* node) {
    if (node == nullptr) {
      return 0;
    }

    assert(node->Parent() == nullptr || node->Parent() != node->Child(Side::LEFT));
    assert(node->Parent() == nullptr || node->Parent() != node->Child(Side::RIGHT));
    assert(node != node->Child(Side::LEFT));
    assert(node != node->Child(Side::RIGHT));
    assert(node != node->Parent());

    auto lhs = node->Child(Side::LEFT);
    auto rhs = node->Child(Side::RIGHT);

    assert(lhs == nullptr || lhs->Parent() == node);
    assert(rhs == nullptr || rhs->Parent() == node);

    auto lheight = Height(lhs);
    auto rheight = Height(rhs);

    assert(node->bias == BiasOf(lheight <=> rheight));
    assert(std::abs(lheight - rheight) <= 1);

    return std::max(lheight, rheight) + 1;
  }

  Node nil_ = {};
};

}  // namespace bst::avl