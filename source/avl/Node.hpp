#pragma once

#include <ostream>

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

template <WeaklyOrdered K>
std::ostream& operator<<(std::ostream& out, AVLNode<K>& node) {
  return out << "(" << node.key << " " << node.bias << ")";
}

}  // namespace avl