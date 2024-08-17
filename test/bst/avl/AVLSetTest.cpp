#include <gtest/gtest.h>

#include "bst/avl/Tree.hpp"
#include "bst/set/TestConstruction.hpp"
#include "bst/set/TestStdLike.hpp"

namespace bst::avl {

using namespace bst::set;

TEST(AVLSet, StdLike) {
  TestStdLike<AVLTree<K>>("AVLSet");
}

TEST(AVLSet, ConstructFromRange) {
  TestConstructionFromRange<AVLTree<K>>();
}

TEST(AVLSet, ConstructFromInitializerList) {
  TestConstructionFromInitializerList<AVLTree<K>>();
}

TEST(AVLSet, Movable) {
  TestMovable<AVLTree<K>>();
}

}  // namespace bst::avl
