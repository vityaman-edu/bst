#pragma once

#include <optional>
#include <utility>

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"
#include "bst/naive/Insert.hpp"
#include "bst/naive/Node.hpp"
#include "bst/naive/Remove.hpp"

namespace bst::naive {

template <class K>
class NaiveTree {
public:
  using Node = NaiveNode<K>;

  NaiveTree() = default;

  explicit NaiveTree(Node* root) : root_(root) {
    assert(root != nullptr);
  }

  NaiveTree(const NaiveTree&) = delete;
  NaiveTree& operator=(const NaiveTree&) = delete;

  NaiveTree(NaiveTree&& that) noexcept = default;
  NaiveTree& operator=(NaiveTree&&) = default;

  ~NaiveTree() = default;

  bool Insert(Node* node) {
    const auto result = NaiveInsert(root_, node);

    switch (result) {
      case NaiveInsertionResult::EMPTY:
        root_ = node;
        return true;
      case NaiveInsertionResult::EXISTS:
        return false;
      case NaiveInsertionResult::INSERTED:
        return true;
    }

    std::unreachable();
  }

  void Remove(Node* node) {
    std::optional<Node> dummy = std::nullopt;

    if (node->Parent() == nullptr) {
      dummy = Node();
      LinkChild(&dummy.value(), Side::LEFT, node);
    }

    NaiveRemove(node);

    if (dummy != std::nullopt) {
      root_ = dummy->Child(Side::LEFT);
      if (root_ != nullptr) {
        root_->SetParent(nullptr);
      }
    }
  }

  auto* Root(this auto& self) {
    return self.root_;
  }

private:
  Node* root_ = nullptr;
};

}  // namespace bst::naive