#include "bst/core/Side.hpp"

#include <cassert>
#include <compare>
#include <cstdint>
#include <utility>

namespace bst {

Side operator-(Side side) {
  auto num = static_cast<std::int8_t>(side);
  return static_cast<Side>(-num);
}

Side SideOf(std::weak_ordering ordering) {
  if (ordering == std::weak_ordering::less) {
    return Side::LEFT;
  }
  if (ordering == std::weak_ordering::greater) {
    return Side::RIGHT;
  }
  assert(ordering != std::weak_ordering::equivalent);
  std::unreachable();
}

}  // namespace bst