#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bst/core/Tree.hpp"
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

  ASSERT_EQ(ToVector<int>(actual), ToVector<int>(expected));
}

template <BSTTree Tree>
void TestConstructionFromInitializerList() {
  using Set = BSTSet<Tree>;

  Set set = {1, 2, 4};

  std::vector<int> expected = {1, 2, 4};
  ASSERT_EQ(ToVector<int>(set), expected);
}

template <BSTTree Tree>
void TestMovable() {
  using Set = BSTSet<Tree>;

  std::vector<int> expected = {1, 2, 3, 4};

  Set first(expected);
  ASSERT_THAT(ToVector<int>(first), expected);

  Set second = std::move(first);
  ASSERT_THAT(ToVector<int>(second), expected);

  first = std::move(second);
  ASSERT_THAT(ToVector<int>(first), expected);
}

template <BSTTree Tree>
void TestCopyable() {
  using Set = BSTSet<Tree>;

  std::vector<int> expected = {1, 2, 3, 4};

  Set first(expected);

  Set second = first;

  Set third;
  third = first;

  ASSERT_THAT(ToVector<int>(first), expected);
  ASSERT_THAT(ToVector<int>(second), expected);
  ASSERT_THAT(ToVector<int>(third), expected);
}

}  // namespace bst::set