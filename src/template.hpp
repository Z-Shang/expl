#pragma once

#include <functional>
#include <stack>
#include <unordered_map>

#include "heap.hpp"

namespace corel {

using TiStat = int;
auto statInc = [](TiStat s) -> TiStat { return s + 1; };
auto statGet = [](TiStat s) -> int { return s; };

template <typename A>
struct TiState {
  using TiStack_t = std::stack<utils::Addr>;
  using TiDump_t = std::nullptr_t;
  using TiHeap_t = utils::Heap<A>;
  using TiGlobal_t = std::unordered_map<std::string, utils::Addr>;

  TiStack_t _stack;
  TiDump_t _dump;
  TiHeap_t _heap;
  TiGlobal_t _global;
  TiStat _stat;
};

auto applyToStats = []<typename A>(std::function<TiStat(TiStat)> f,
                                   TiState<A> state) -> TiState<A> {
  auto& [s, d, h, g, st] = state;
  return {s, d, h, g, f(st)};
};

template <typename A>
auto initHeap(std::vector<SC<A>> sc_defs)
    -> std::tuple<typename TiState<A>::TiHeap_t,
                  typename TiState<A>::TiGlobal_t> {
  typename TiState<A>::TiHeap_t heap;
  typename TiState<A>::TiGlobal_t global;
  for (auto&& [name, lhs, rhs] : sc_defs) {
    global.insert(heap.allocSC(name, lhs, rhs));
  }
  return {std::forward(heap), std::forward(global)};
}
}  // namespace corel
