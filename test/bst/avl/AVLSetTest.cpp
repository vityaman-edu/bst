#include <gtest/gtest.h>

#include "bst/avl/Tree.hpp"
#include "bst/set/TestStdLike.hpp"

namespace bst::avl {

TEST(AVLSet, StdLike) {
  using namespace bst::set;
  TestStdLike<AVLTree<K>>("AVLSet");
}

}  // namespace bst::avl
