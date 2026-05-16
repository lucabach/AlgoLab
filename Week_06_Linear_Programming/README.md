# Week 6 — Linear Programming

Linear Programming (LP) allows optimizing a linear objective subject to linear constraints — a powerful generalization of many combinatorial problems. In AlgoLab, LP is solved via CGAL's `solve_linear_program` or `solve_quadratic_program`.

The challenge is **modeling**: translating the problem's constraints into LP form correctly. Pay special attention to variable bounds and whether you need the exact or inexact kernel.

---

## Problems

| Problem | Core Technique | Status |
|---------|---------------|--------|
| [Maximize It!](Maximize_it_/) | LP introduction — basic linear program setup | Complete |
| [Diet](Diet/) | LP — nutrient constraints with min cost | Complete |
| [Inball](Inball/) | LP — largest ball inside a convex polygon | Complete |
| [Casterly Rock](Casterly_Rock/) | LP — resource allocation under constraints | Complete |

---

## Key Concepts

### CGAL LP Setup
```cpp
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

Program lp(CGAL::SMALLER, true, 0, false, 0); // <= constraints, x >= 0
// lp.set_a(col, row, coeff)  — constraint matrix
// lp.set_b(row, rhs)         — right-hand side
// lp.set_c(col, coeff)       — objective (minimize by default)

Solution s = CGAL::solve_linear_program(lp, ET());
if (s.is_infeasible()) { ... }
if (s.is_unbounded())  { ... }
// s.objective_value() — returns exact rational
```

### Modeling Tips
- Negate objective to maximize (CGAL minimizes by default)
- Use `CGAL::LARGER` for >= constraints, or negate the row
- Inball: the constraint is `a·c + r·||a|| ≤ b` for each half-plane `a·x ≤ b`
- Always check feasibility and unboundedness before reading the solution

### When to Use LP vs Flow
- Flow: integral solution needed, graph structure present
- LP: fractional solutions OK, or constraints don't fit a network
