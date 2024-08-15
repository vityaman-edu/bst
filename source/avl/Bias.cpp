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

Bias operator-(Bias bias) {
  switch (bias) {
    case Bias::LEFT:
      return Bias::RIGHT;
    case Bias::RIGHT:
      return Bias::LEFT;
    case Bias::NONE:
      return Bias::NONE;
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