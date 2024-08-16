#include "bst/naive/NodeFactory.hpp"
#include "bst/naive/Tree.hpp"

namespace bst {

template <class K>
using NaiveNodeFactory = bst::naive::NaiveNodeFactory<K>;

template <class K>
using NaiveNode = bst::naive::NaiveNode<K>;

template <class K>
using NaiveTree = bst::naive::NaiveTree<K>;

/**
 * Example
 * ---
 *      8
 *   3   10
 * 1  6     14
 *   4 7  13
 */
template <WeaklyOrdered K>
inline std::tuple<NaiveNodeFactory<K>, NaiveTree<K>> Example() {
  NaiveNodeFactory<K> bst;
  NaiveNode<K>* root =
      bst(8, bst(3, bst(1), bst(6, bst(4), bst(7))), bst(10, nullptr, bst(14, bst(13))));
  return {std::move(bst), NaiveTree<K>(root)};
}

}  // namespace bst
