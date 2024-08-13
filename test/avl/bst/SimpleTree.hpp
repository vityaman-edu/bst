#pragma once

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