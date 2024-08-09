#include "avl/Bias.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <utility>

#include "avl/bst/Side.hpp"

namespace avl {

Bias BiasOf(Side side) {
  switch (side) {
    case Side::LEFT:
      return Bias::LEFT;
    case Side::RIGHT:
      return Bias::RIGHT;
  }
  std::unreachable();
}

Bias operator+(Bias lhs, Bias rhs) {
  auto lnum = static_cast<std::int8_t>(lhs);
  auto rnum = static_cast<std::int8_t>(rhs);
  assert(std::abs(lnum + rnum) <= 1);
  return static_cast<Bias>(lnum + rnum);
}

Bias& operator+=(Bias& lhs, Bias rhs) {
  return lhs = lhs + rhs;
}

}  // namespace avl