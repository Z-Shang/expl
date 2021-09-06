#pragma once

#include <variant>
#include <vector>

#include "template.hpp"

namespace corel {

/*
 * tiFinal :: TiState -> Bool
 * tiFinal ([sole_addr], dump, heap, globals, stats)
 * = isDataNode (hLookup heap sole_addr)
 * tiFinal ([], dump, heap, globals, stats) = error "Empty stack!"
 * tiFinal state = False
 */

template <typename A>
auto finalP(TiState<A> state) -> bool {
  auto& [stack, dump, heap, global, stat] = state;
  if (stack.empty()) throw "Empty stack!";
  if (stack.size() > 1) return false;
  return utils::dataNodeP(heap.lookup(stack.top()));
}

template <typename A>
auto doAdmin(TiState<A> state) -> TiState<A> {
  return applyToStats(statInc, state);
}

template <typename A>
auto step(TiState<A> state) -> TiState<A> {
  return state;
};

template <typename A>
auto eval(TiState<A> state) -> std::vector<TiState<A>> {
  auto next_state = doAdmin(step(state));
  if (finalP(state)) return {state};
  auto rest = eval(next_state);
  auto res = {state};
  res.insert(res.end(), std::make_move_iterator(rest.begin()),
             std::make_move_iterator(rest.end()));
  return res;
}
}  // namespace corel
