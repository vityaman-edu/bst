#include <gtest/gtest.h>

#include "bst/TestStdLike.hpp"
#include "bst/naive/Tree.hpp"

namespace bst::naive {

TEST(NaiveSet, StdLike) {
  TestStdLike<NaiveTree<K>>("NaiveSet");
}

}  // namespace bst::naive
