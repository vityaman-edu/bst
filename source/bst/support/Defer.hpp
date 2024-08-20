#pragma once

#include <concepts>
#include <utility>

namespace bst {

template <std::invocable Action>
class Defer {
public:
  Defer(Action action) : action_(std::move(action)) {  // NOLINT
  }

  Defer(const Defer&) = delete;
  Defer(Defer&&) = delete;
  Defer& operator=(const Defer&) = delete;
  Defer& operator=(Defer&&) = delete;

  ~Defer() {
    std::move(action_)();
  }

private:
  Action action_;
};

}  // namespace bst