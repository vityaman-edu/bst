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

Bias BiasOf(std::weak_ordering order);

Bias operator-(Bias bias);

Bias operator+(Bias lhs, Bias rhs);

Bias& operator+=(Bias& lhs, Bias rhs);

std::ostream& operator<<(std::ostream& out, Bias bias);

}  // namespace avl