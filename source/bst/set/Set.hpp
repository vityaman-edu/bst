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
      size_ += 1;
    }
  }

  void Remove(const K& item) {
    auto* node = Find(item);
    if (node != nullptr) {
      size_ -= 1;
      tree_.Remove(node);
      delete node;  // NOLINT(cppcoreguidelines-owning-memory)
    }
  }

  bool Contains(const K& item) {
    return Find(item) != nullptr;
  }

  [[nodiscard]] std::size_t Size() const {
    return size_;
  }

  [[nodiscard]] bool IsEmpty() const {
    return Size() == 0;
  }

  MutIterator<Node> begin() {  // NOLINT(readability-identifier-naming)
    auto* root = tree_.Root();
    if (root == nullptr) {
      return end();
    }
    return MutIterator<Node>(Min(root));
  }

  MutIterator<Node> end() {  // NOLINT(readability-identifier-naming)
    return MutIterator<Node>();
  }

private:
  Node* Find(const K& item) {
    auto* root = tree_.Root();
    if (root == nullptr) {
      return nullptr;
    }
    return Search(tree_.Root(), item);
  }

  void Free(Node* node) {
    if (node == nullptr) {
      return;
    }
    Free(node->left);
    Free(node->right);
    delete node;  // NOLINT(cppcoreguidelines-owning-memory)
  }

  Tree tree_;
  std::size_t size_ = 0;
};

}  // namespace bst::set