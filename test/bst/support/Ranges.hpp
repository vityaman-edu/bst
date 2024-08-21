#pragma once

#include <ranges>
#include <vector>

namespace bst {

template <class T>
std::vector<T> ToVector(const std::ranges::range auto& range) {
  std::vector<T> vector;
  for (const auto& element : range) {
    vector.emplace_back(element);
  }
  return vector;
}

}  // namespace bst