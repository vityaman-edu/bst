#pragma once

#include <cstddef>
#include <iostream>

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst {

template <ReadonlyBSTNode Node>
void Print(const Node* root, std::size_t indent = 0) {
  if (root == nullptr) {
    return;
  }
  Print(root->Child(Side::RIGHT), indent + 1);
  std::cerr << std::string(2 * indent, ' ') << "(" << root->Key() << " -> " << root->Value() << ")"
            << std::endl;
  Print(root->Child(Side::LEFT), indent + 1);
}

}  // namespace bst