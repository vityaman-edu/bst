#pragma once

#include <deque>

#include "avl/bst/Node.hpp"
#include "avl/bst/Side.hpp"
#include "avl/bst/SimpleNode.hpp"

namespace avl::test {

template <WeaklyOrdered K>
class SimpleNodeFactory {
public:
  using Node = SimpleNode<K>;

  Node* operator()(Node::Key key, Node* lhs = nullptr, Node* rhs = nullptr) {
    nodes_.push_back({.key = key});
    Node* node = &nodes_.back();
    LinkChild(node, Side::LEFT, lhs);
    LinkChild(node, Side::RIGHT, rhs);
    return node;
  }

private:
  std::deque<Node> nodes_;
};

}  // namespace avl::test