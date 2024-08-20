#pragma once

#include <variant>

#include "bst/core/Node.hpp"
#include "bst/support/TemplateNode.hpp"

namespace bst::naive {

template <WeaklyOrdered K, class V = std::monostate>
struct NaiveNode final : TemplateNode<K, V, NaiveNode<K>> {
  NaiveNode() = default;

  explicit NaiveNode(K key) : TemplateNode<K, V, NaiveNode<K>>(std::move(key)) {
  }
};

}  // namespace bst::naive
