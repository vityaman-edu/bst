#pragma once

#include <concepts>
#include <utility>

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst {

template <class V>
struct EmptyUpdateCallback {
  void operator()(V* /*parent*/, const V* /*lhs*/, const V* /*rhs*/) {
    // Do nothing
  }
};

template <
    BSTNode Node,
    class V = typename Node::ValueType,
    std::invocable<V*, const V*, const V*> Update = EmptyUpdateCallback<V>>
class AdaptedUpdateCallback {
public:
  explicit AdaptedUpdateCallback(Update origin) : origin_(std::move(origin)) {
  }

  void operator()(Node* parent) {
    const Node* lhs = parent->Child(Side::LEFT);
    const Node* rhs = parent->Child(Side::RIGHT);

    V* pval = &parent->Value();
    const V* lval = ((lhs != nullptr) ? (&lhs->Value()) : (nullptr));
    const V* rval = ((rhs != nullptr) ? (&rhs->Value()) : (nullptr));

    origin_(pval, lval, rval);
  }

private:
  Update origin_;
};

template <BSTNode Node>
auto Adapted(auto callback) {
  using V = typename Node::ValueType;
  return AdaptedUpdateCallback<Node, V, decltype(callback)>(std::move(callback));
}

}  // namespace bst