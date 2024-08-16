#include <gtest/gtest.h>

#include "bst/naive/Tree.hpp"
#include "bst/set/TestConstruction.hpp"
#include "bst/set/TestStdLike.hpp"

namespace bst::naive {

using namespace bst::set;

TEST(NaiveSet, StdLike) {
  TestStdLike<NaiveTree<K>>("NaiveSet");
}

TEST(NaiveSet, ConstructFromInitializerList) {
  TestConstructionFromInitializerList<NaiveTree<K>>();
}

}  // namespace bst::naive
