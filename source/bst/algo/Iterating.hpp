#pragma once

#include "bst/core/Node.hpp"

namespace bst {

template <BSTNode Node, std::invocable<Node*> Action>
void IteratingOverBranchFrom(Node* node, Action action) {
  while (node != nullptr) {
    action(node);
    node = node->Parent();
  }
}

}  // namespace bst