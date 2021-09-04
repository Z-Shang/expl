#pragma once

#include <string>

#include "core.hpp"

namespace corel {

template <typename A>
auto parse(std::string) -> Prog<A>;

}
