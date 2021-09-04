#pragma once

#include <string>
#include <tuple>
#include <variant>
#include <vector>

namespace corel {

using std::tuple;
using std::vector;

using Name = std::string;
using Num = int;

enum Arith { ADD, SUB, MUL, DIV };

enum Rel { LE, LT, GE, GT, EQ, NE };

enum Bool { AND, OR };

template <typename A>
struct App;

template <typename A>
struct Let;

template <typename A>
struct Case;

template <typename A>
struct Lam;

template <typename A>
using Expr = std::variant<Name, Num, tuple<Num, Num>, App<A> *, Let<A> *,
                          Case<A> *, Lam<A> *>;

template <typename A>
using def = tuple<A, Expr<A>>;

template <typename A>
using Alt = tuple<Num, vector<Name>, Expr<A>>;

template <typename A>
struct App {
  Expr<A> M;
  Expr<A> N;
};

template <typename A>
struct Let {
  const bool recp;
  vector<def<A>> defs;
  Expr<A> body;
};

template <typename A>
struct Case {
  Expr<A> expr;
  vector<Alt<A>> alters;
};

template <typename A>
struct Lam {
  vector<A> arg;
  Expr<A> body;
};

template <typename A>
struct SC {
  Name name;
  vector<Name> lhs;
  Expr<A> rhs;
};

template <typename A>
using Prog = vector<SC<A>>;

using CoreExpr = Expr<Name>;
using CoreProg = Prog<Name>;
}  // namespace corel
