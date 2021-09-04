#pragma once

#include <vector>

#include "template.hpp"

namespace corel {
template <typename A>
auto eval(TiState<A>) -> std::vector<TiState<A>>;
}
