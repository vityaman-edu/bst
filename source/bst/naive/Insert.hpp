#pragma once

#include <compare>
#include <cstdint>

#include "bst/algo/Iterating.hpp"
#include "bst/core/Node.hpp"

namespace bst::naive {

enum class NaiveInsertionResult : std::uint8_t { EMPTY, EXISTS, INSERTED };

template <BSTNode Node>
NaiveInsertionResult NaiveInsert(Node* root, Node* newbie) {
  if (root == nullptr) {
    return NaiveInsertionResult::EMPTY;
  }

  auto [parent, order] = SearchParent(root, newbie->Key());
  if (order == std::weak_ordering::equivalent) {
    return NaiveInsertionResult::EXISTS;
  }

  LinkChild(parent, SideOf(order), newbie);
  return NaiveInsertionResult::INSERTED;
}

template <BSTNode Node, std::invocable<Node*> OnChildrenChanged>
NaiveInsertionResult NaiveInsert(Node* root, Node* newbie, OnChildrenChanged notify) {
  const auto result = NaiveInsert(root, newbie);
  if (result == NaiveInsertionResult::INSERTED) {
    IteratingOverBranchFrom(newbie->Parent(), notify);
  }
  return result;
}

}  // namespace bst::naive