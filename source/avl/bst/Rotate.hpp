#pragma once

#include "avl/bst/Core.hpp"
#include "avl/bst/Side.hpp"

namespace avl {

template <BSTNode Node>
void Rotate(Side side, Node* upper) {
  assert(upper->parent != nullptr);
  auto* lower = Child(Reversed(side), upper);
  Child(Reversed(side), upper) = Child(side, lower);
  if (Child(side, lower) != nullptr) {
    Child(side, lower)->parent = upper;
  }
  lower->parent = upper->parent;
  if (upper->parent->left == upper) {
    upper->parent->left = lower;
  } else {
    upper->parent->right = lower;
  }
  Child(side, lower) = upper;
  upper->parent = lower;
}

}  // namespace avl