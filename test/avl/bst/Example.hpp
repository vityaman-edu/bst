#include "avl/bst/NodeFactory.hpp"
#include "avl/bst/SimpleTree.hpp"

namespace avl::test {

/**
 * Example
 * ---
 *      8
 *   3   10
 * 1  6     14
 *   4 7  13
 */
template <WeaklyOrdered K>
inline std::tuple<SimpleNodeFactory<K>, SimpleTree<K>> Example() {
  SimpleNodeFactory<K> bst;
  SimpleNode<K>* root =
      bst(8, bst(3, bst(1), bst(6, bst(4), bst(7))), bst(10, nullptr, bst(14, bst(13))));
  return {std::move(bst), SimpleTree<K>(root)};
}

}  // namespace avl::test
