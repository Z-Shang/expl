#pragma once

#include <string>
#include <tuple>
#include <variant>
#include <vector>

#include "core.hpp"

namespace corel {
namespace utils {
using Addr = std::size_t;
using NAp = std::tuple<Addr, Addr>;
using NNum = int;

template <typename A>
struct NSC {
  std::string name;
  std::vector<std::string> args;
  Expr<A> expr;
};

template <typename A>
using Node = std::variant<NAp, NNum, NSC<A>>;

auto dataNodeP = []<typename A>(Node<A> n) {
  return std::holds_alternative<utils::NNum>(n);
};

template <typename A>
struct Heap {
  size_t nelem;
  std::vector<Node<A>> _store;

  auto allocSC(std::string name, std::vector<std::string> args, Expr<A> body)
      -> std::tuple<std::string, Addr> {
    _store.emplace_back(name, args, body);
    return {name, _store.size()};
  }

  bool empty() const noexcept { return _store.empty(); }
  size_t size() const noexcept { return _store.size(); }

  auto lookup(auto addr) const { return _store[addr]; }
};

}  // namespace utils
}  // namespace corel
