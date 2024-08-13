#pragma once

#include <deque>

#include "avl/bst/MutIterator.hpp"
#include "avl/bst/Search.hpp"
#include "avl/bst/Tree.hpp"

namespace avl {

template <BSTTree Tree>
class BSTSet {
private:
  using Node = Tree::Node;

public:
  using K = Node::Key;

  void Add(K item) {
    nodes_.push_back(Node{std::move(item)});
    auto* node = &nodes_.back();
    bool is_inserted = tree_.Insert(node);
    if (!is_inserted) {
      nodes_.pop_back();
    }
  }

  bool Contains(const K& item) {
    auto* root = tree_.Root();
    return root != tree_.Nil() && Search(tree_, root, item) != tree_.Nil();
  }

  MutIterator<Tree> begin() {  // NOLINT(readability-identifier-naming)
    auto* root = tree_.Root();
    if (root == tree_.Nil()) {
      return end();
    }
    return MutIterator<Tree>(&tree_, Min(tree_, root));
  }

  MutIterator<Tree> end() {  // NOLINT(readability-identifier-naming)
    return MutIterator<Tree>();
  }

private:
  Tree tree_;
  std::deque<Node> nodes_;
};

}  // namespace avl