#include "avl/Bias.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <utility>

#include "avl/bst/Side.hpp"

namespace avl {

Bias BiasOf(Side side) {
  const auto num = static_cast<std::int8_t>(side);
  return static_cast<Bias>(num);
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
      return out << "OO";
    case Bias::LEFT:
      return out << "LO";
    case Bias::RIGHT:
      return out << "OR";
  }
  std::unreachable();
}

}  // namespace avl