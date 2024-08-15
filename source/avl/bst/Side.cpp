#include "avl/bst/Side.hpp"

#include <compare>
#include <utility>

namespace avl {

Side Reversed(Side side) {
  switch (side) {
    case Side::LEFT:
      return Side::RIGHT;
    case Side::RIGHT:
      return Side::LEFT;
  }
  std::unreachable();
}

Side SideOf(std::weak_ordering ordering) {
  if (ordering == std::weak_ordering::less) {
    return Side::LEFT;
  }
  if (ordering == std::weak_ordering::greater) {
    return Side::RIGHT;
  }
  std::unreachable();
}

std::ostream& operator<<(std::ostream& out, Side side) {
  switch (side) {
    case Side::LEFT:
      return out << "LEFT";
    case Side::RIGHT:
      return out << "RIGHT";
  }
  std::unreachable();
}

}  // namespace avl