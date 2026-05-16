# Week 7 — CGAL: Computational Geometry

This week dives into the **Computational Geometry Algorithms Library (CGAL)**. CGAL's key advantage is exact arithmetic — it uses arbitrary-precision kernels to avoid floating-point errors that would otherwise corrupt geometric computations.

The main data structure this week is the **Delaunay triangulation**: given a set of points, it builds a triangulation where no point lies inside the circumscribed circle of any triangle. Many proximity and connectivity queries reduce to queries on this triangulation.

---

## Problems

| Problem | Core Technique | Status |
|---------|---------------|--------|
| [Bistro](Bistro/) | Delaunay triangulation — nearest neighbor queries | Complete |
| [Germs](Germs/) | Delaunay — minimum spanning tree of circle radii | Complete |
| [H1N1](H1N1/) | Delaunay — pathfinding between Voronoi cells | Complete |
| [Clues](Clues/) | Delaunay + 2-coloring (bipartite check) | Complete |
| [Idefix](Idefix/) | Delaunay — union-find on edges by length | Complete |

---

## Key Concepts

### Delaunay Triangulation (CGAL)
```cpp
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef K::Point_2 Point;

Delaunay dt;
dt.insert(points.begin(), points.end());

// Nearest neighbor
auto vertex = dt.nearest_vertex(query_point);
```

### Voronoi Diagram (dual of Delaunay)
The Delaunay triangulation and Voronoi diagram are duals. The Voronoi cell of a point p contains all locations closer to p than to any other point. Useful for "which region does a query point belong to?"

### Exact vs Inexact Kernel
- `Exact_predicates_inexact_constructions_kernel` (EPICK): fast, coordinates are doubles; predicates (inside/outside) are exact
- `Exact_predicates_exact_constructions_kernel` (EPECK): fully exact but slower; needed when you compute intersections or distances algebraically

### Squared Distances
Always compare squared distances to avoid `sqrt()`. CGAL's `CGAL::squared_distance(p, q)` works with both kernels.
