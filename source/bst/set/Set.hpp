#pragma once

#include <cstddef>
#include <initializer_list>
#include <ranges>
#include <variant>

#include "bst/algo/Bound.hpp"
#include "bst/algo/Search.hpp"
#include "bst/core/Side.hpp"
#include "bst/core/Tree.hpp"
#include "bst/core/UpdateCallback.hpp"
#include "bst/core/WeaklyOrdered.hpp"
#include "bst/set/ConstIterator.hpp"
#include "bst/set/MutIterator.hpp"
#include "bst/support/Update.hpp"

namespace bst::set {

template <
    template <class, class, class>
    class Tree,
    WeaklyOrdered K,
    class V = std::monostate,
    UpdateCallback<V> Update = EmptyUpdateCallback<V>>
class BSTSet {
private:
  using UsedTree = Tree<K, V, Update>;
  static_assert(BSTTree<UsedTree>);

  using Node = UsedTree::Node;

public:
  using Iterator = MutIterator<Node>;
  using ReadonlyIterator = ConstIterator<Node>;

  BSTSet() = default;

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
    auto iterator = Find(item);
    if (iterator == end()) {
      return;
    }
    Remove(iterator);
  }

  void Remove(Iterator iterator) {
    Node* node = iterator.NodePtr();
    size_ -= 1;
    tree_.Remove(node);
    delete node;  // NOLINT(cppcoreguidelines-owning-memory)
  }

  Iterator Find(const K& item) {
    return Iterator(Search(tree_.Root(), item));
  }

  ReadonlyIterator Find(const K& item) const {
    return ReadonlyIterator(Search(tree_.Root(), item));
  }

  bool Contains(const K& item) const {
    return Find(item) != end();
  }

  [[nodiscard]] Iterator LowerBound(const K& item) {
    return Iterator(bst::LowerBound(tree_.Root(), item));
  }

  [[nodiscard]] ReadonlyIterator LowerBound(const K& item) const {
    return ReadonlyIterator(bst::LowerBound(tree_.Root(), item));
  }

  [[nodiscard]] Iterator UpperBound(const K& item) {
    return Iterator(bst::UpperBound(tree_.Root(), item));
  }

  [[nodiscard]] ReadonlyIterator UpperBound(const K& item) const {
    return ReadonlyIterator(bst::UpperBound(tree_.Root(), item));
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
    return Iterator(Min(tree_.Root()));
  }

  Iterator end() {  // NOLINT(readability-identifier-naming)
    return Iterator(nullptr);
  }

  ReadonlyIterator begin() const {  // NOLINT(readability-identifier-naming)
    return ReadonlyIterator(Min(tree_.Root()));
  }

  ReadonlyIterator end() const {  // NOLINT(readability-identifier-naming)
    return ReadonlyIterator(nullptr);
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

  UsedTree tree_;
  std::size_t size_ = 0;
};

}  // namespace bst::set