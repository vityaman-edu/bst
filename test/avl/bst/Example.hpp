#include <deque>

#include "avl/bst/Core.hpp"
#include "avl/bst/Side.hpp"

namespace avl::test {

struct Node {
  using Key = int;

  Key key = 0;
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
};

class Nodes {
public:
  Node* operator()(Node::Key key, Node* lhs = nullptr, Node* rhs = nullptr) {
    nodes_.push_back({.key = key});
    Node* node = &nodes_.back();
    LinkChild(node, Side::LEFT, lhs);
    LinkChild(node, Side::RIGHT, rhs);
    return node;
  }

private:
  std::deque<Node> nodes_;
};

/**
 * Example
 * ---
 *      8
 *   3   10
 * 1  6     14
 *   4 7  13
 */
inline std::tuple<Nodes, Node*> Example() {
  Nodes bst;
  Node* root =
      bst(8,
          bst(3, bst(1), bst(6, bst(4), bst(7))),
          bst(10, nullptr, bst(14, bst(13))));
  return {std::move(bst), root};
}

}  // namespace avl::test
