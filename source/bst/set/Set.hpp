#pragma once

#include "bst/Search.hpp"
#include "bst/Tree.hpp"
#include "bst/set/MutIterator.hpp"

namespace bst::set {

template <BSTTree Tree>
class BSTSet {
private:
  using Node = Tree::Node;

public:
  using K = Node::Key;

  BSTSet() = default;

  BSTSet(const BSTSet&) = delete;
  BSTSet(BSTSet&&) = delete;
  BSTSet& operator=(const BSTSet&) = delete;
  BSTSet& operator=(BSTSet&&) = delete;

  ~BSTSet() {
    Free(tree_.Root());
  }

  void Add(const K& item) {
    if (!Contains(item)) {
      tree_.Insert(new Node(std::move(item)));
    }
  }

  void Remove(const K& item) {
    auto* node = Find(item);
    if (node != tree_.Nil()) {
      tree_.Remove(node);
      delete node;  // NOLINT(cppcoreguidelines-owning-memory)
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

  void Free(Node* node) {
    if (node == tree_.Nil()) {
      return;
    }
    Free(node->left);
    Free(node->right);
    delete node;  // NOLINT(cppcoreguidelines-owning-memory)
  }

  Tree tree_;
};

}  // namespace bst::set