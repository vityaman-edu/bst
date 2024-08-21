#pragma once

#include "bst/algo/Adjacent.hpp"
#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst::naive {

template <BSTNode Node>
struct NaiveRemovalResult {
  struct {
    Node* node;
    Side side;
  } shrinked;
  Node* successor = nullptr;
};

template <BSTNode Node>
NaiveRemovalResult<Node> NaiveRemove(Node* node) {
  NaiveRemovalResult<Node> result;

  if (node->Child(Side::LEFT) == nullptr && node->Child(Side::RIGHT) == nullptr) {
    result.shrinked = {.node = node->Parent(), .side = SideOf(node)};
    node->Parent()->SetChild(SideOf(node), nullptr);
  } else if (node->Child(Side::LEFT) == nullptr || node->Child(Side::RIGHT) == nullptr) {
    result.shrinked = {.node = node->Parent(), .side = SideOf(node)};
    Node* child =
        ((node->Child(Side::LEFT) == nullptr)  //
             ? (node->Child(Side::RIGHT))
             : (node->Child(Side::LEFT)));
    LinkChild(node->Parent(), SideOf(node), child);
  } else {
    Node* successor = Successor(node);

    result.successor = successor;
    result.shrinked = {.node = successor->Parent(), .side = SideOf(successor)};
    if (result.shrinked.node == node) {
      result.shrinked.node = successor;
    }

    LinkChild(successor->Parent(), SideOf(successor), successor->Child(Side::RIGHT));
    LinkChild(node->Parent(), SideOf(node), successor);
    for (auto side : {Side::LEFT, Side::RIGHT}) {
      LinkChild(successor, side, node->Child(side));
    }
  }

  return result;
}

template <BSTNode Node, std::invocable<Node*> OnChildrenChanged>
NaiveRemovalResult<Node> NaiveRemove(Node* node, OnChildrenChanged notify) {
  const auto result = NaiveRemove(node);
  IteratingOverBranchFrom(result.shrinked.node, notify);
  IteratingOverBranchFrom(node->Parent(), notify);
  return result;
}

}  // namespace bst::naive