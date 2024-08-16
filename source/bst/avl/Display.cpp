#include "bst/avl/Display.hpp"

#include <ostream>
#include <utility>

#include "bst/avl/Bias.hpp"

namespace bst::avl {

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

}  // namespace bst::avl