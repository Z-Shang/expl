#pragma once

#include <iostream>

#include "core.hpp"
#include "prelude.hpp"
#include "template.hpp"

namespace corel {

template <typename A>
auto compile(Prog<A> prog) -> TiState<A> {
  auto pre = prelude();
  prog.insert(prog.end(), std::make_move_iterator(pre.begin()),
              std::make_move_iterator(pre.end()));
  auto sc_defs = prog;
  auto [_heap, _global] = initHeap(sc_defs);
  auto addr_of_main = _global.find("main");
  if (addr_of_main == _global.end()) {
    std::cerr << "main is not defined" << std::endl;
    exit(1);
  }
  return TiState<A>{
      {addr_of_main}, nullptr, std::forward(_heap), std::forward(_global), 0};
}
}  // namespace corel
