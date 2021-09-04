#pragma once

#include "compile.hpp"
#include "core.hpp"
#include "eval.hpp"
#include "parse.hpp"
#include "show.hpp"
#include "template.hpp"

namespace corel {
template <typename A>
auto run(std::string input) -> std::string {
  return show(eval(compile(parse(input))));
}
}  // namespace corel
