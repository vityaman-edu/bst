#pragma once

#include "bst/core/Node.hpp"
#include "bst/support/TemplateNode.hpp"

namespace bst::naive {

template <WeaklyOrdered K>
struct NaiveNode final : TemplateNode<K, NaiveNode<K>> {
  NaiveNode() = default;

  explicit NaiveNode(K key) : TemplateNode<K, NaiveNode<K>>(std::move(key)) {
  }
};

}  // namespace bst::naive
