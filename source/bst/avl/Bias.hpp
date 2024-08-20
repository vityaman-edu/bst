#pragma once

#include <compare>
#include <cstdint>

#include "bst/core/Side.hpp"

namespace bst::avl {

enum class Bias : std::int8_t {
  NONE = 0,
  LEFT = -1,
  RIGHT = +1,
};

Bias BiasOf(Side side);

Bias BiasOf(std::weak_ordering order);

Bias operator-(Bias bias);

Bias operator+(Bias lhs, Bias rhs);

Bias& operator+=(Bias& lhs, Bias rhs);

}  // namespace bst::avl