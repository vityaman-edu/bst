#include "avl/Hello.hpp"
#include "gtest/gtest.h"

namespace avl::test {

TEST(Hello, Basic) {
  ASSERT_EQ(avl::Hello(), "Hello, AVL");
}

}  // namespace avl::test