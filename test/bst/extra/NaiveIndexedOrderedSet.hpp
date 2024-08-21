#pragma once

#include <algorithm>
#include <vector>

#include "bst/core/Node.hpp"

namespace bst::extra {

template <WeaklyOrdered K>
class NaiveIndexedOrderedSet final {
public:
  void Add(const K& item) {
    if (!Contains(item)) {
      elements_.insert(std::upper_bound(begin(), end(), item), item);
    }
  }

  void Remove(const K& item) {
    if (!Contains(item)) {
      std::ranges::remove(elements_, item);
    }
  }

  bool Contains(const K& item) {
    return std::ranges::binary_search(elements_, item);
  }

  [[nodiscard]] std::size_t Size() const {
    return elements_.size();
  }

  const K& At(std::size_t index) const {
    return elements_.at(index);
  }

  void Clear() {
    elements_.clear();
  }

  auto begin() const {
    return elements_.begin();
  }

  auto end() const {
    return elements_.end();
  }

private:
  std::vector<K> elements_;
};

}  // namespace bst::extra