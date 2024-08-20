#pragma once

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst {

template <BSTNode Node>
void Rotate(Side side, Node* upper) {
  auto* lower = Child(-side, upper);
  LinkChild(upper, -side, Child(side, lower));
  LinkChild(upper->parent, SideOf(upper), lower);
  LinkChild(lower, side, upper);
}

template <BSTNode Node>
void DoubleRotate(Side side, Node* upper) {
  Rotate(-side, Child(-side, upper));
  Rotate(side, upper);
}

}  // namespace bst