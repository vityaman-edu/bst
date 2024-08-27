#pragma once

#include <compare>
#include <concepts>

#include "bst/support/Unreachable.hpp"

namespace bst {

template <class T>
concept WeaklyOrdered = requires(const T& lhs, const T& rhs) {
  { lhs <=> rhs } -> std::convertible_to<std::weak_ordering>;
};

}  // namespace bst