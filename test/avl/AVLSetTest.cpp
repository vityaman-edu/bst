#include <gtest/gtest.h>

#include "avl/Tree.hpp"
#include "avl/bst/TestStdLike.hpp"

namespace avl::test {

TEST(AVLSet, StdLike) {
  TestStdLike<AVLTree<K>>("AVLSet");
}

}  // namespace avl::test
