# Week 11 — Mixed Topics

Later-semester problems that demand combining multiple algorithmic techniques. No single "theme" — you need to recognize which tools to combine.

---

## Problems

| Problem | Core Technique | Status |
|---------|---------------|--------|
| [Evolution](Evolution/) | LCA (lowest common ancestor) on tree | Complete |
| [Harry Potter](Harry_Potter/) | CGAL — Delaunay + union-find + binary search | Complete |
| [Marathon](Marathon/) | Dijkstra with flow capacity constraints | Complete |
| [The Stymphalian Birds](The_Stymphalian_Birds/) | LP + geometry | Complete |

---

## Key Concepts

### Lowest Common Ancestor (LCA)
Preprocess a tree with binary lifting (sparse table on ancestors) for O(log n) LCA queries. Useful for "what is the common ancestor of two nodes?" and path-query problems.

### Combining Dijkstra + Flow
Model the problem as a graph where edges have both a cost (for shortest path) and a capacity (for flow). Run Dijkstra to find the shortest path, then route flow along it (Bellman-Ford / SPFA if negative weights appear in residual graph).
