#pragma once

namespace bst {

template <class V>
struct EmptyUpdate {
  void operator()(V& /*parent*/, const V& /*left*/, const V& /*right*/) {
    // Do nothing
  }
};

}  // namespace bst