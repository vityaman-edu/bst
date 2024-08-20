#pragma once

#include <algorithm>

#include "bst/avl/Node.hpp"

namespace bst::avl {

template <WeaklyOrdered K>
std::int64_t Height(AVLNode<K>* node) {
  if (node == nullptr) {
    return 0;
  }

  assert(node->Parent() == nullptr || node->Parent() != node->Child(Side::LEFT));
  assert(node->Parent() == nullptr || node->Parent() != node->Child(Side::RIGHT));
  assert(node != node->Child(Side::LEFT));
  assert(node != node->Child(Side::RIGHT));
  assert(node != node->Parent());

  auto lhs = node->Child(Side::LEFT);
  auto rhs = node->Child(Side::RIGHT);

  assert(lhs == nullptr || lhs->Parent() == node);
  assert(rhs == nullptr || rhs->Parent() == node);

  auto lheight = Height(lhs);
  auto rheight = Height(rhs);

  assert(node->Bias() == BiasOf(lheight <=> rheight));
  assert(std::abs(lheight - rheight) <= 1);

  return std::max(lheight, rheight) + 1;
}

}  // namespace bst::avl