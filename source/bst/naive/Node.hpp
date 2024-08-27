#pragma once

#include <variant>

#include "bst/core/WeaklyOrdered.hpp"
#include "bst/support/TemplateNode.hpp"

namespace bst::naive {

template <WeaklyOrdered K, class V = std::monostate>
struct NaiveNode final : TemplateNode<K, V, NaiveNode<K, V>> {
  NaiveNode() = default;

  explicit NaiveNode(K key, V value = {})
      : TemplateNode<K, V, NaiveNode<K, V>>(std::move(key), std::move(value)) {
  }
};

}  // namespace bst::naive
