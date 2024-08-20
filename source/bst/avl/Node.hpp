#pragma once

#include "bst/avl/Bias.hpp"
#include "bst/core/Node.hpp"
#include "bst/help/TemplateNode.hpp"

namespace bst::avl {

template <WeaklyOrdered K>
struct AVLNode final : public TemplateNode<K, AVLNode<K>> {
  AVLNode() = default;

  explicit AVLNode(K key) : TemplateNode<K, AVLNode<K>>(std::move(key)) {
  }

  Bias bias = Bias::NONE;
};

}  // namespace bst::avl