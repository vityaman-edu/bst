#pragma once

#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <ranges>

#include "bst/algo/Search.hpp"
#include "bst/core/Side.hpp"
#include "bst/core/Tree.hpp"
#include "bst/set/ConstIterator.hpp"
#include "bst/set/MutIterator.hpp"
#include "bst/support/Update.hpp"

namespace bst::set {

template <
    BSTTree Tree,
    std::invocable<typename Tree::Node*> Update = EmptyUpdate<typename Tree::Node>>
class BSTSet {
private:
  using Node = Tree::Node;

public:
  using K = Node::KeyType;

  using Iterator = MutIterator<Node>;
  using ReadonlyIterator = ConstIterator<Node>;

  BSTSet() = default;

  explicit BSTSet(Update update) : tree_(std::move(update)) {
  }

  BSTSet(const std::initializer_list<K>& list) {
    Assign(list);
  }

  template <std::ranges::range Range>
  explicit BSTSet(const Range& range) {
    Assign(range);
  }

  BSTSet(const BSTSet& that) {
    Assign(that);
  }

  BSTSet& operator=(const BSTSet& that) {
    if (this != &that) {
      Assign(that);
    }
    return *this;
  }

  BSTSet(BSTSet&& that) noexcept {
    Swap(that);
  }

  BSTSet& operator=(BSTSet&& that) noexcept {
    if (this != &that) {
      Swap(that);
    }
    return *this;
  }

  ~BSTSet() {
    Clear();
  }

  void Add(const K& item) {
    if (!Contains(item)) {
      tree_.Insert(new Node(std::move(item)));
      size_ += 1;
    }
  }

  void Remove(const K& item) {
    auto iter = Find(item);
    if (iter == end()) {
      return;
    }
    Node* node = iter.NodePtr();
    size_ -= 1;
    tree_.Remove(node);
    delete node;  // NOLINT(cppcoreguidelines-owning-memory)
  }

  Iterator Find(const K& item) {
    Node* node = Search(tree_.Root(), item);
    if (node == nullptr) {
      return end();
    }
    return Iterator(node);
  }

  ReadonlyIterator Find(const K& item) const {
    const Node* node = Search(tree_.Root(), item);
    if (node == nullptr) {
      return end();
    }
    return ReadonlyIterator(node);
  }

  bool Contains(const K& item) const {
    return Find(item) != end();
  }

  [[nodiscard]] std::size_t Size() const {
    return size_;
  }

  [[nodiscard]] bool IsEmpty() const {
    return Size() == 0;
  }

  void Clear() {
    Free(tree_.Root());
    tree_ = {};
    size_ = 0;
  }

  Iterator begin() {  // NOLINT(readability-identifier-naming)
    auto* root = tree_.Root();
    if (root == nullptr) {
      return end();
    }
    return Iterator(Min(root));
  }

  Iterator end() {  // NOLINT(readability-identifier-naming)
    return Iterator();
  }

  ReadonlyIterator begin() const {  // NOLINT(readability-identifier-naming)
    const Node* root = tree_.Root();
    if (root == nullptr) {
      return end();
    }
    return ReadonlyIterator(Min(root));
  }

  ReadonlyIterator end() const {  // NOLINT(readability-identifier-naming)
    return ReadonlyIterator();
  }

protected:
  const Node* Root() const {
    return tree_.Root();
  }

private:
  template <std::ranges::range Range>
  void Assign(const Range& range) {
    Clear();
    for (const auto& element : range) {
      Add(element);
    }
  }

  void Swap(BSTSet& that) {
    std::swap(this->tree_, that.tree_);
    std::swap(this->size_, that.size_);
  }

  void Free(Node* node) {
    if (node == nullptr) {
      return;
    }
    Free(node->Child(Side::LEFT));
    Free(node->Child(Side::RIGHT));
    delete node;  // NOLINT(cppcoreguidelines-owning-memory)
  }

  Tree tree_;
  std::size_t size_ = 0;
};

}  // namespace bst::set