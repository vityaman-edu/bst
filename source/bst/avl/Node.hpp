#pragma once

#include <ostream>

#include "bst/Node.hpp"
#include "bst/avl/Bias.hpp"

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

template <WeaklyOrdered K>
std::ostream& operator<<(std::ostream& out, AVLNode<K>& node) {
  return out << "(" << node.key << " " << node.bias << ")";
}

}  // namespace bst::avl