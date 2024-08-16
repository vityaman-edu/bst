#pragma once

namespace bst {

template <class K>
struct SimpleNode {
  using Key = K;

  Key key;
  SimpleNode* parent = nullptr;
  SimpleNode* left = nullptr;
  SimpleNode* right = nullptr;
};

}  // namespace bst