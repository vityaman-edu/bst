#pragma once

#include "bst/core/Node.hpp"

namespace bst {

template <BSTNode Node>
struct EmptyUpdate {
  void operator()(Node* /*parent*/) {
    // Do nothing
  }
};

}  // namespace bst