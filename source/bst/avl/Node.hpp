#pragma once

#include "bst/avl/Bias.hpp"
#include "bst/core/Node.hpp"
#include "bst/support/TemplateNode.hpp"

namespace bst::avl {

template <WeaklyOrdered K>
struct AVLNode final : public TemplateNode<K, AVLNode<K>> {
  AVLNode() = default;

  explicit AVLNode(K key) : TemplateNode<K, AVLNode<K>>(std::move(key)) {
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