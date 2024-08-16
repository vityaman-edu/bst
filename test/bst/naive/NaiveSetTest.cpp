#include <gtest/gtest.h>

#include "bst/naive/Tree.hpp"
#include "bst/set/TestStdLike.hpp"

namespace bst::naive {

TEST(NaiveSet, StdLike) {
  bst::set::TestStdLike<NaiveTree<bst::set::K>>("NaiveSet");
}

}  // namespace bst::naive
