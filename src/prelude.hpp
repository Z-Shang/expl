#pragma once

#include "core.hpp"

namespace corel {

auto prelude() -> CoreProg {
        return {
            {"I", {"x"}, "x"},
            {"K", {"x", "y"}, "x"},
            {"K1", {"x", "y"}, "y"},
            {"S",
             {"f", "g", "x"},
             new App<Name>{new App<Name>{"f", "x"}, new App<Name>{"g", "x"}}},
            {"compose",
             {"f", "g", "x"},
             {new App<Name>{"f", new App<Name>{"g", "x"}}}},
            {"twice",
             {"f"},
             new App<Name>{new App<Name>{"compose", "f"}, "f"}}};
}

}  // namespace corel
