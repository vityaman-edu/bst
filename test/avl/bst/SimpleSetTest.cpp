#include <gtest/gtest.h>

#include "avl/bst/SimpleTree.hpp"
#include "avl/bst/TestStdLike.hpp"

namespace avl::test {

TEST(SimpleSet, StdLike) {
  TestStdLike<SimpleTree<K>>("SimpleSet");
}

}  // namespace avl::test
