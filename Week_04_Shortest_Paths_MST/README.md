# Week 4 — Shortest Paths & Minimum Spanning Trees

Shortest-path and spanning-tree algorithms are workhorses of graph algorithms. This week covers **Dijkstra**, **Bellman-Ford**, **Kruskal/Prim**, and their combination with greedy or binary-search strategies.

A key theme: many problems reduce to "build the right graph, then run a standard algorithm." Recognizing this reduction is the hard part.

---

## Problems

| Problem | Core Technique | Status |
|---------|---------------|--------|
| [Asterix the Gaul](Asterix_the_Gaul/) | Binary search + Dijkstra | Complete |
| [Attack of the Clones](Attack_of_the_Clones/) | Kruskal MST on interval graph | Complete |
| [Boats](Boats/) | Greedy interval scheduling | Complete |
| [Moving Books](Moving_Books/) | Greedy — sort by weight | Complete |
| [Worm Kingdom](Worm_Kingdom/) | Dijkstra on layered / state-augmented graph | Complete |
| [Kingdom Defense](Kingdom_Defense/) | Max flow on layered graph | Complete |

---

## Key Concepts

### Dijkstra (BGL)
```cpp
std::vector<int> dist(n, INT_MAX);
boost::dijkstra_shortest_paths(G, source,
    boost::distance_map(boost::make_iterator_property_map(
        dist.begin(), boost::get(boost::vertex_index, G))));
```
Only works with non-negative edge weights.

### Kruskal MST (BGL)
```cpp
std::vector<Edge> mst_edges;
boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst_edges));
```

### Binary Search on Answer
Many optimization problems become decision problems: "Is cost ≤ X feasible?" Binary search on X, then check feasibility with BFS/Dijkstra.

### Greedy Interval Scheduling
Sort by end time, greedily pick non-overlapping intervals. Prove correctness via exchange argument.
