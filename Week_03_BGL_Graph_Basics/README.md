# Week 3 — BGL: Graph Traversal & Basics

This week introduces the **Boost Graph Library (BGL)** — the main graph toolkit used throughout AlgoLab. You will learn to build graphs, run BFS/DFS, find connected components, compute articulation points and bridges, and work with geometric intersection graphs.

BGL uses a generic, template-heavy interface. The upside: algorithms compose cleanly. The downside: compile errors are cryptic. Read the BGL documentation carefully.

---

## Problems

| Problem | Core Technique | Status |
|---------|---------------|--------|
| [First Steps with BGL](First_steps_with_BGL/) | BGL setup — BFS, connected components | Complete |
| [Ant Challenge](Ant_Challenge/) | Minimum spanning tree + Dijkstra on subgraph | Complete |
| [Buddy Selection](Buddy_Selection/) | Maximum matching on general graph | Complete |
| [Important Bridges](Important_Bridges/) | Bridge finding — biconnected components | Complete |
| [Hit](Hit/) | CGAL — ray-segment intersection | Complete |
| [First Hit](First_Hit/) | CGAL — nearest intersection along a ray | Complete |
| [Hiking Maps](Hiking_Maps/) | Sliding window on triangle containment | Complete |
| [Antenna](Antenna/) | CGAL — smallest enclosing circle | Complete |
| [Motorcycles](Motorcycles/) | CGAL — half-plane / ray intersection sorting | Complete |

---

## Key Concepts

### BGL Graph Types
```cpp
// Undirected graph with edge weights
typedef boost::adjacency_list<
    boost::vecS, boost::vecS, boost::undirectedS,
    boost::no_property,
    boost::property<boost::edge_weight_t, int>
> Graph;
```

### BFS / Connected Components
```cpp
std::vector<int> comp(n);
int num_comp = boost::connected_components(G, &comp[0]);
```

### Bridge Finding
Use `boost::biconnected_components` — edges not in any biconnected component are bridges.

### CGAL Ray Intersection
```cpp
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 Segment;
typedef K::Ray_2 Ray;
// CGAL::do_intersect(ray, seg) — exact arithmetic, no floating-point errors
```

### Sliding Window on Geometry
Sort events, use a multiset or deque to maintain a window of active objects as you sweep.
