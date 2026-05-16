# Week 10 — Advanced Algorithms

A mix of harder problems that combine multiple techniques — flow, DP, geometry, and spanning trees used together.

---

## Problems

| Problem | Core Technique | Status | Notes |
|---------|---------------|--------|-------|
| [Asterix and the Chariot Race](Asterix_and_the_Chariot_Race/) | Weighted matching / spanning structures | **Incomplete** | Only main() stub present |
| [Legions](Legions/) | LP / parametric shortest path | Complete | |
| [Return of the Jedi](Return_of_the_Jedi/) | Second-minimum spanning tree | Complete | |
| [Sith](Sith/) | Delaunay + sliding window on edge lengths | Complete | |
| [The Empire Strikes Back](The_Empire_Strikes_Back/) | LP + geometry | Complete | |

---

## Key Concepts

### Second-Minimum Spanning Tree
Build the MST, then for each non-tree edge `(u,v,w)`, consider swapping it with the maximum-weight edge on the path `u→v` in the MST. The best such swap gives the second-minimum spanning tree.

### Parametric / Binary Search Approaches
Some problems have a parameter you can binary-search on, then check feasibility with flow or LP at each step.
