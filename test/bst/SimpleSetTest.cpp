#include <gtest/gtest.h>

#include "bst/SimpleTree.hpp"
#include "bst/TestStdLike.hpp"

namespace bst {

TEST(SimpleSet, StdLike) {
  TestStdLike<SimpleTree<K>>("SimpleSet");
}

}  // namespace bst
