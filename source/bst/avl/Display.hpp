#pragma once

#include <ostream>

#include "bst/Node.hpp"
#include "bst/avl/Bias.hpp"
#include "bst/avl/Node.hpp"

namespace bst::avl {

std::ostream& operator<<(std::ostream& out, Bias bias);

template <WeaklyOrdered K>
std::ostream& operator<<(std::ostream& out, AVLNode<K>& node) {
  return out << "(" << node.key << " " << node.bias << ")";
}

}  // namespace bst::avl