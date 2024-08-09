#pragma once

#include "avl/bst/Node.hpp"
#include "avl/bst/Side.hpp"

namespace avl {

template <BSTNode Node>
void Rotate(Side side, Node* upper) {
  assert(upper->parent != nullptr);
  auto* lower = Child(Reversed(side), upper);
  LinkChild(upper, Reversed(side), Child(side, lower));
  LinkChild(upper->parent, SideOf(upper), lower);
  LinkChild(lower, side, upper);
}

template <BSTNode Node>
void DoubleRotate(Side side, Node* upper) {
  Rotate(Reversed(side), Child(Reversed(side), upper));
  Rotate(side, upper);
}

}  // namespace avl