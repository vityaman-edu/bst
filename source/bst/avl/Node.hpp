#pragma once

#include <variant>

#include "bst/avl/Bias.hpp"
#include "bst/core/Node.hpp"
#include "bst/support/TemplateNode.hpp"

namespace bst::avl {

template <WeaklyOrdered K, class V = std::monostate>
struct AVLNode final : public TemplateNode<K, V, AVLNode<K, V>> {
  AVLNode() = default;

  explicit AVLNode(K key) : TemplateNode<K, V, AVLNode<K, V>>(std::move(key)) {
  }

  void SetBias(Bias bias) {
    bias_ = bias;
  }

  [[nodiscard]] enum Bias Bias() const {
    return bias_;
  }

private:
  enum Bias bias_ = Bias::NONE;
};

}  // namespace bst::avl