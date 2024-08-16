#pragma once

#include <deque>

#include "bst/Node.hpp"
#include "bst/Side.hpp"
#include "bst/SimpleNode.hpp"

namespace bst {

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

}  // namespace bst