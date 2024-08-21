#pragma once

#include <concepts>

#include "bst/core/Node.hpp"
#include "bst/core/Side.hpp"

namespace bst {

/**
 * @cite Cormen, Introduction to Algorithms,
 *       Chapter 13, Red-Black Trees, p. 336
 *
 *         9               9  <- root
 *        /               /
 *       7    left       5    <- upper
 *      /\    <----     /\
 *     5 8             4 7    <- lower
 *    /\      ---->     /\
 *   4 6      right    6 8
 */
template <BSTNode Node>
void Rotate(Side side, Node* upper) {
  auto* lower = upper->Child(-side);
  LinkChild(upper, -side, lower->Child(side));
  LinkChild(upper->Parent(), SideOf(upper), lower);
  LinkChild(lower, side, upper);
}

template <BSTNode Node, std::invocable<Node*> OnChildrenChanged>
void Rotate(Side side, Node* upper, OnChildrenChanged notify) {
  Rotate(side, upper);
  for (Node* node : {upper, upper->Parent(), upper->Parent()->Parent()}) {
    notify(node);
  }
}

/**
 * @cite https://github.com/ebiggers/avl_tree
 *
 *          9             9            9
 *         /             /            /
 *        7 <- upper -> 7            5
 *       / \           / \        /    \
 *      3  8   =>     5  8  =>   3      7
 *     / \           / \        / \    / \
 *    2   5         3   6      2   4  6   8
 *       / \       / \
 *      4   6     2   4
 */
template <BSTNode Node>
void DoubleRotate(Side side, Node* upper) {
  Rotate(-side, upper->Child(-side));
  Rotate(side, upper);
}

// TODO(vityaman): DoubleRotate body code repeat
template <BSTNode Node, std::invocable<Node*> OnChildrenChanged>
void DoubleRotate(Side side, Node* upper, OnChildrenChanged notify) {
  Rotate(-side, upper->Child(-side), notify);
  Rotate(side, upper, notify);
}

}  // namespace bst