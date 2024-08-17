#pragma once

#include <compare>
#include <optional>

#include "bst/Adjacent.hpp"
#include "bst/Node.hpp"
#include "bst/Search.hpp"
#include "bst/Side.hpp"
#include "bst/naive/Node.hpp"

namespace bst::naive {

template <class K>
class NaiveTree {
public:
  using Node = NaiveNode<K>;

  NaiveTree() = default;

  explicit NaiveTree(Node* root) : root_(root) {
    assert(root != nullptr);
  }

  NaiveTree(const NaiveTree&) = delete;
  NaiveTree& operator=(const NaiveTree&) = delete;

  NaiveTree(NaiveTree&& that) noexcept = default;
  NaiveTree& operator=(NaiveTree&&) = default;

  ~NaiveTree() = default;

  bool Insert(Node* node) {
    if (root_ == nullptr) {
      root_ = node;
      return true;
    }

    auto [parent, order] = SearchParent(root_, node->key);
    if (order == std::weak_ordering::equivalent) {
      return false;
    }

    LinkChild(parent, SideOf(order), node);
    return true;
  }

  void Remove(Node* node) {
    assert(node != nullptr);

    std::optional<Node> dummy = std::nullopt;

    if (node->parent == nullptr) {
      dummy = Node();
      LinkChild(&dummy.value(), Side::LEFT, node);
    }

    if (node->left == nullptr && node->right == nullptr) {
      Child(SideOf(node), node->parent) = nullptr;
    } else if (node->left == nullptr || node->right == nullptr) {
      Node* child = node->left == nullptr ? node->right : node->left;
      LinkChild(node->parent, SideOf(node), child);
    } else {
      Node* successor = Successor(node);
      LinkChild(successor->parent, SideOf(successor), successor->right);
      LinkChild(node->parent, SideOf(node), successor);
      for (auto side : {Side::LEFT, Side::RIGHT}) {
        LinkChild(successor, side, Child(side, node));
      }
    }

    if (dummy != std::nullopt) {
      root_ = dummy->left;
      if (root_ != nullptr) {
        root_->parent = nullptr;
      }
    }
  }

  Node* Root() const {
    return root_;
  }

private:
  Node* root_ = nullptr;
};

}  // namespace bst::naive