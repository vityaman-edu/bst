#pragma once

#include "avl/bst/Core.hpp"
#include "avl/bst/Side.hpp"

namespace avl {

template <BSTNode Node>
void Rotate(Side side, Node* upper) {
  assert(upper->parent != nullptr);
  auto* lower = Child(Reversed(side), upper);
  LinkChild(upper, Reversed(side), Child(side, lower));
  auto upper_side = (upper->parent->left == upper) ? Side::LEFT : Side::RIGHT;
  LinkChild(upper->parent, upper_side, lower);
  LinkChild(lower, side, upper);
}

}  // namespace avl