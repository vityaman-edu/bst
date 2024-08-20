#pragma once

#include <deque>

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"
#include "bst/naive/Node.hpp"

namespace bst::naive {

template <WeaklyOrdered K>
class NaiveNodeFactory {
public:
  using Node = NaiveNode<K>;

  Node* operator()(Node::KeyType key, Node* lhs = nullptr, Node* rhs = nullptr) {
    nodes_.emplace_back(std::move(key));
    Node* node = &nodes_.back();
    LinkChild(node, Side::LEFT, lhs);
    LinkChild(node, Side::RIGHT, rhs);
    return node;
  }

private:
  std::deque<Node> nodes_;
};

}  // namespace bst::naive