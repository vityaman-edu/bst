#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ranges>

#include "bst/Tree.hpp"
#include "bst/set/Set.hpp"

namespace bst::set {

template <BSTTree Tree>
void TestConstructionFromRange() {
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

template <BSTTree Tree>
void TestConstructionFromInitializerList() {
  using Set = BSTSet<Tree>;

  Set set = {1, 2, 4};

  std::vector<int> expected = {1, 2, 4};
  ASSERT_EQ(set | std::ranges::to<std::vector>(), expected);
}

template <BSTTree Tree>
void TestMovable() {
  using Set = BSTSet<Tree>;

  std::vector<int> expected = {1, 2, 3, 4};

  Set first(expected);
  ASSERT_THAT(first | std::ranges::to<std::vector>(), expected);

  Set second = std::move(first);
  ASSERT_THAT(second | std::ranges::to<std::vector>(), expected);

  first = std::move(second);
  ASSERT_THAT(first | std::ranges::to<std::vector>(), expected);
}

template <BSTTree Tree>
void TestCopyable() {
  using Set = BSTSet<Tree>;

  std::vector<int> expected = {1, 2, 3, 4};

  Set first(expected);

  Set second = first;

  Set third;
  third = first;

  ASSERT_THAT(first | std::ranges::to<std::vector>(), expected);
  ASSERT_THAT(second | std::ranges::to<std::vector>(), expected);
  ASSERT_THAT(third | std::ranges::to<std::vector>(), expected);
}

}  // namespace bst::set