# ETH Zurich — Algorithm Lab (AlgoLab)

Competitive-programming course at ETH Zurich. Problems are solved in **C++17** using the **Boost Graph Library (BGL)** and **CGAL** (Computational Geometry Algorithms Library). Each week introduces a new algorithmic paradigm; problems escalate in difficulty and require combining multiple techniques.

All source code is in `src/main.cpp`. Problem statements are in `this.pdf`. The `public/` folder contains sample and graded test cases.

---

## Progress Overview

| Week | Topic | Problems | Completed |
|------|-------|----------|-----------|
| [Week 1](Week_01_Intro/) | Intro — Prefix Sums & Sliding Window | 6 | 6 / 6 |
| [Week 2](Week_02_Dynamic_Programming/) | Dynamic Programming | 6 | 6 / 6 |
| [Week 3](Week_03_BGL_Graph_Basics/) | BGL — Graph Traversal & Basics | 9 | 9 / 9 |
| [Week 4](Week_04_Shortest_Paths_MST/) | Shortest Paths & Minimum Spanning Trees | 6 | 6 / 6 |
| [Week 5](Week_05_Maximum_Flow/) | Maximum Flow | 5 | 5 / 5 |
| [Week 6](Week_06_Linear_Programming/) | Linear Programming (LP) | 4 | 4 / 4 |
| [Week 7](Week_07_CGAL_Geometry/) | CGAL — Computational Geometry | 5 | 5 / 5 |
| [Week 8](Week_08_Advanced_Flow_Matching/) | Advanced Flow & Matching | 6 | 6 / 6 |
| [Week 9](Week_09_Min_Cost_Flow/) | Minimum-Cost Flow | 4 | 4 / 4 |
| [Week 10](Week_10_Advanced_Algorithms/) | Advanced Algorithms | 5 | 4 / 5 |
| [Week 11](Week_11_Mixed_Topics/) | Mixed Topics | 4 | 4 / 4 |
| [Week 12](Week_12_Final_Problems/) | Final Problems | 5 | 3 / 5 |

**Total: 63 / 65 problems attempted, 60 / 65 complete**

> Problems marked **Incomplete** have an empty or stub `main.cpp`.

---

## Tech Stack

| Tool | Purpose |
|------|---------|
| C++17 | Implementation language |
| [Boost Graph Library (BGL)](https://www.boost.org/doc/libs/release/libs/graph/) | Graph algorithms (BFS, Dijkstra, max flow, min-cost flow, matching) |
| [CGAL](https://www.cgal.org/) | Computational geometry (Delaunay triangulation, convex hull, linear programming) |
| Code Expert | ETH's online judge and submission platform |

### Typical includes

```cpp
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
```

---

## How to Compile

```bash
# Standard compile (adapt flags for your system)
g++ -std=c++17 -O2 -o solution src/main.cpp \
    -lboost_graph -lCGAL -lgmp -lmpfr

# Run with test input
./solution < public/sample.in
```

On ETH's Code Expert platform, compilation and testing is handled automatically.

---

## Course Structure

Each week's folder contains individual problem directories. Inside each:

```
ProblemName/
├── src/
│   └── main.cpp        # Student solution
├── public/
│   ├── sample.in/out   # Sample test cases
│   ├── test1.in/out    # Graded test cases
│   └── ...
└── this.pdf            # Problem statement
```

---

## Key Algorithmic Patterns

| Pattern | Weeks Used | BGL/CGAL Tool |
|---------|------------|---------------|
| Prefix sums & sliding window | 1 | — |
| Dynamic programming on intervals | 2 | — |
| BFS / DFS / Connected components | 3 | `boost::breadth_first_search` |
| Dijkstra's shortest path | 4 | `boost::dijkstra_shortest_paths` |
| Kruskal's MST | 4 | `boost::kruskal_minimum_spanning_tree` |
| Push-relabel max flow | 5, 8 | `boost::push_relabel_max_flow` |
| LP / quadratic programming | 6 | `CGAL::solve_linear_program` |
| Delaunay triangulation | 7 | `CGAL::Delaunay_triangulation_2` |
| Min-cost max flow | 9 | `boost::successive_shortest_paths_nonneg_weights` |
| Maximum bipartite matching | 8, 10 | `boost::maximum_weighted_matching` |
