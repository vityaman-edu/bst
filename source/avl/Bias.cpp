#include "avl/Bias.hpp"

#include <cassert>
#include <compare>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <utility>

#include "avl/bst/Side.hpp"

namespace avl {

Bias BiasOf(Side side) {
  const auto num = static_cast<std::int8_t>(side);
  return static_cast<Bias>(num);
}

Bias BiasOf(std::weak_ordering order) {
  if (order == std::weak_ordering::less) {
    return Bias::RIGHT;
  }
  if (order == std::weak_ordering::greater) {
    return Bias::LEFT;
  }
  assert(order == std::weak_ordering::equivalent);
  return Bias::NONE;
}

Bias operator-(Bias bias) {
  const auto num = static_cast<std::int8_t>(bias);
  return static_cast<Bias>(-num);
}

Bias operator+(Bias lhs, Bias rhs) {
  const auto lnum = static_cast<std::int8_t>(lhs);
  const auto rnum = static_cast<std::int8_t>(rhs);
  assert(std::abs(lnum + rnum) <= 1);
  return static_cast<Bias>(lnum + rnum);
}

Bias& operator+=(Bias& lhs, Bias rhs) {
  return lhs = lhs + rhs;
}

std::ostream& operator<<(std::ostream& out, Bias bias) {
  switch (bias) {
    case Bias::NONE:
      return out << "O";
    case Bias::LEFT:
      return out << "L";
    case Bias::RIGHT:
      return out << "R";
  }
  std::unreachable();
}

}  // namespace avl