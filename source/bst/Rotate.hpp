#pragma once

#include "bst/Node.hpp"
#include "bst/Side.hpp"

namespace bst {

template <BSTNode Node>
void Rotate(Side side, Node* upper) {
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

}  // namespace bst