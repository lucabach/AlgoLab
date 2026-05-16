# Sith

Given n planets appearing in order (the first k are already destroyed), and a connection radius r, find the maximum k such that min(k, largest_connected_component(remaining planets)) is maximized.

## Approach

- Binary search on k (the number of planets already gone). For each candidate k, build a Delaunay triangulation of planets k..n-1 and BFS over Delaunay edges within radius r to find the largest connected component.
- Use the invariant that the answer is max over k of min(k, component_size(k)) to guide the binary search.
