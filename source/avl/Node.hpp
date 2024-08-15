#pragma once

#include "avl/Bias.hpp"
#include "avl/bst/Node.hpp"

namespace avl {

template <WeaklyOrdered K>
struct AVLNode {
  using Key = K;

  Key key;
  AVLNode* parent = nullptr;
  AVLNode* left = nullptr;
  AVLNode* right = nullptr;
  Bias bias = Bias::NONE;
};



}  // namespace avl