#include <gtest/gtest.h>

#include "bst/TestStdLike.hpp"
#include "bst/avl/Tree.hpp"

namespace bst::avl {

TEST(AVLSet, StdLike) {
  TestStdLike<AVLTree<K>>("AVLSet");
}

}  // namespace bst::avl
