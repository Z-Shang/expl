#pragma once

#include <string>
#include <vector>

#include "template.hpp"

namespace corel {
template <typename A>
auto show(std::vector<TiState<A>>) -> std::string;
}
