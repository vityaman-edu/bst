#pragma once

#include <cstddef>
#include <ostream>

#include "bst/Node.hpp"
#include "bst/Side.hpp"
#include "bst/Tree.hpp"

namespace bst {

template <BSTTree Tree, BSTNode Node = typename Tree::Node>
void Print(std::ostream& out, Tree& tree, Node* node = nullptr, std::size_t indent = 0) {
  if (node == nullptr) {
    node = tree.Root();
  }

  if (node == tree.Nil()) {
    return;
  }

  Print(out, tree, Child(Side::RIGHT, node), indent + 1);
  out << std::string(2 * indent, ' ') << *node << std::endl;
  Print(out, tree, Child(Side::LEFT, node), indent + 1);
}

}  // namespace bst