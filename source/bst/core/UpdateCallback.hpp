#pragma once

#include <concepts>

namespace bst {

template <class Callback, class V>
concept UpdateCallback = std::invocable<Callback, V*, const V*, const V*>;

}  // namespace bst
