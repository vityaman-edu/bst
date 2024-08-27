#include <gtest/gtest.h>

#include "bst/naive/Tree.hpp"
#include "bst/set/TestConstruction.hpp"
#include "bst/set/TestStdLike.hpp"

namespace bst::naive {

using namespace bst::set;

TEST(NaiveSet, StdLike) {
  TestStdLike<NaiveTree>("NaiveSet");
}

TEST(NaiveSet, ConstructFromRange) {
  TestConstructionFromRange<NaiveTree, K>();
}

TEST(NaiveSet, ConstructFromInitializerList) {
  TestConstructionFromInitializerList<NaiveTree, K>();
}

TEST(NaiveSet, Movable) {
  TestMovable<NaiveTree, K>();
}

TEST(NaiveSet, Copyable) {
  TestCopyable<NaiveTree, K>();
}

}  // namespace bst::naive
