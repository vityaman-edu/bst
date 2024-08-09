#pragma once

#include <deque>

#include "avl/bst/Node.hpp"
#include "avl/bst/Side.hpp"

namespace avl::test {

template <BSTNode Node>
class NodeFactory {
public:
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