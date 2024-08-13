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

  void Remove(const K& item) {
    auto* node = Find(item);
    if (node != tree_.Nil()) {
      tree_.Remove(node);
    }
  }

  bool Contains(const K& item) {
    return Find(item) != tree_.Nil();
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
  Node* Find(const K& item) {
    auto* root = tree_.Root();
    if (root == tree_.Nil()) {
      return tree_.Nil();
    }
    return Search(tree_, tree_.Root(), item);
  }

  Tree tree_;
  std::deque<Node> nodes_;
};

}  // namespace avl