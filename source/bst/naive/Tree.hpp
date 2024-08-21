#pragma once

#include <concepts>
#include <optional>
#include <utility>
#include <variant>

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"
#include "bst/naive/Insert.hpp"
#include "bst/naive/Node.hpp"
#include "bst/naive/Remove.hpp"
#include "bst/support/Update.hpp"

namespace bst::naive {

template <
    WeaklyOrdered K,
    class V = std::monostate,
    std::invocable<NaiveNode<K, V>*> Update = EmptyUpdate<NaiveNode<K, V>>>
class NaiveTree {
public:
  using Node = NaiveNode<K, V>;

  NaiveTree() = default;

  explicit NaiveTree(Update update) : update_(std::move(update)) {
  }

  explicit NaiveTree(Node* root) : root_(root) {
    assert(root != nullptr);
  }

  NaiveTree(const NaiveTree&) = delete;
  NaiveTree& operator=(const NaiveTree&) = delete;

  NaiveTree(NaiveTree&& that) noexcept = default;
  NaiveTree& operator=(NaiveTree&&) = default;

  ~NaiveTree() = default;

  bool Insert(Node* node) {
    const auto result = NaiveInsert(root_, node, update_);

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

    NaiveRemove(node, update_);

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
  Update update_ = {};
};

}  // namespace bst::naive