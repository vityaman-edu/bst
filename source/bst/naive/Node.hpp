#pragma once

#include "bst/Node.hpp"

namespace bst::naive {

template <WeaklyOrdered K>
struct NaiveNode {
  using Key = K;

  Key key;
  NaiveNode* parent = nullptr;
  NaiveNode* left = nullptr;
  NaiveNode* right = nullptr;
};

}  // namespace bst::naive
