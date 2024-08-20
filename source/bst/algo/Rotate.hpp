#pragma once

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst {

template <BSTNode Node>
void Rotate(Side side, Node* upper) {
  auto* lower = upper->Child(-side);
  LinkChild(upper, -side, lower->Child(side));
  LinkChild(upper->Parent(), SideOf(upper), lower);
  LinkChild(lower, side, upper);
}

template <BSTNode Node>
void DoubleRotate(Side side, Node* upper) {
  Rotate(-side, upper->Child(-side));
  Rotate(side, upper);
}

}  // namespace bst