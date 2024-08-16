#pragma once

#include "bst/Tree.hpp"
#include "bst/set/Set.hpp"

namespace bst::set {

template <BSTTree Tree>
void TestConstructionFromInitializerList() {
  using Set = BSTSet<Tree>;

  auto elements = {7, 4, 2, 5, 7, 2};

  Set actual = elements;

  Set expected;
  for (auto element : elements) {
    expected.Add(element);
  }

  auto actual_items = actual | std::ranges::to<std::vector>();
  auto expected_items = expected | std::ranges::to<std::vector>();
  ASSERT_EQ(actual_items, expected_items);
}

}  // namespace bst::set