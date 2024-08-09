#pragma once

#include <compare>
#include <cstdint>

namespace avl {

enum class Side : std::uint8_t { LEFT, RIGHT };

Side Reversed(Side side);

Side SideOf(std::weak_ordering order);

}  // namespace avl