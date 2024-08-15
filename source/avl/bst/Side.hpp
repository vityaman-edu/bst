#pragma once

#include <compare>
#include <cstdint>
#include <ostream>

namespace avl {

enum class Side : std::int8_t { LEFT = -1, RIGHT = +1 };

Side Reversed(Side side);

Side SideOf(std::weak_ordering order);

std::ostream& operator<<(std::ostream& out, Side side);

}  // namespace avl