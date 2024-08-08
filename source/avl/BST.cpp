#include "avl/BST.hpp"

#include <compare>
#include <utility>

namespace avl {

Direction DirectionOf(std::weak_ordering ordering) {
  if (ordering == std::weak_ordering::less) {
    return Direction::LEFT;
  }
  if (ordering == std::weak_ordering::greater) {
    return Direction::RIGHT;
  }
  std::unreachable();
}

}  // namespace avl