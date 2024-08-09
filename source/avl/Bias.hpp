#pragma once

#include <cstdint>

#include "avl/bst/Side.hpp"

namespace avl {

enum class Bias : std::int8_t {
  NONE = 0,
  LEFT = -1,
  RIGHT = +1,
};

Bias BiasOf(Side side);

Bias operator+(Bias lhs, Bias rhs);

Bias& operator+=(Bias& lhs, Bias rhs);

}  // namespace avl