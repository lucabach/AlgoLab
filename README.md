# AlgoLab

Competitive programming course at ETH Zurich. Problems are solved in **C++17** using the **Boost Graph Library (BGL)** and **CGAL**. Each week covers a new algorithmic topic; problems escalate in difficulty and often require combining multiple techniques.

Source code in `src/main.cpp`. Problem statements in `this.pdf`. Test cases in `public/`.

---

## Weeks

| Week | Topic |
|------|-------|
| [Week 1](Week_01_Intro/) | Intro — Prefix Sums & Sliding Window |
| [Week 2](Week_02_Dynamic_Programming/) | Dynamic Programming |
| [Week 3](Week_03_BGL_Graph_Basics/) | BGL — Graph Traversal & Basics |
| [Week 4](Week_04_Shortest_Paths_MST/) | Shortest Paths & Minimum Spanning Trees |
| [Week 5](Week_05_Maximum_Flow/) | Maximum Flow |
| [Week 6](Week_06_Linear_Programming/) | Linear Programming |
| [Week 7](Week_07_CGAL_Geometry/) | CGAL — Computational Geometry |
| [Week 8](Week_08_Advanced_Flow_Matching/) | Advanced Flow & Matching |
| [Week 9](Week_09_Min_Cost_Flow/) | Minimum-Cost Flow |
| [Week 10](Week_10_Advanced_Algorithms/) | Advanced Algorithms |
| [Week 11](Week_11_Mixed_Topics/) | Mixed Topics |
| [Week 12](Week_12_Final_Problems/) | Final Problems |

---

## Tech Stack

| Tool | Purpose |
|------|---------|
| C++17 | Implementation language |
| [Boost Graph Library](https://www.boost.org/doc/libs/release/libs/graph/) | Graphs, flow, matching |
| [CGAL](https://www.cgal.org/) | Geometry, LP, Delaunay |

---

## How to Compile

```bash
g++ -std=c++17 -O2 -o solution src/main.cpp -lboost_graph -lCGAL -lgmp -lmpfr
./solution < public/sample.in
```
