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

  Node* Root() {
    return root_;
  }

private:
  Node* root_ = nullptr;
};

}  // namespace avl::test