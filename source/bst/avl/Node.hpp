#pragma once

#include "bst/avl/Bias.hpp"
#include "bst/core/Node.hpp"

namespace bst::avl {

template <WeaklyOrdered K>
struct AVLNode {
  using Key = K;

  Key key;
  AVLNode* parent = nullptr;
  AVLNode* left = nullptr;
  AVLNode* right = nullptr;
  Bias bias = Bias::NONE;
};

}  // namespace bst::avl