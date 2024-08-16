#include <gtest/gtest.h>

#include "bst/avl/Tree.hpp"
#include "bst/set/TestConstruction.hpp"
#include "bst/set/TestStdLike.hpp"

namespace bst::avl {

using namespace bst::set;

TEST(AVLSet, StdLike) {
  TestStdLike<AVLTree<K>>("AVLSet");
}

TEST(AVLSet, ConstructFromInitializerList) {
  TestConstructionFromInitializerList<AVLTree<K>>();
}

}  // namespace bst::avl
