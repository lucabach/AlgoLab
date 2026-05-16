# Idefix

Given trees connected if within distance s, and bones that belong to a tree's component if within distance s/2, find the minimum squared radius needed so that at least k bones are reachable from one connected component.

## Approach

- Build a Delaunay triangulation of the trees and BFS over Delaunay edges within distance s to assign connected components.
- Count bones per component (those close enough to any tree). If any component already has k bones, output the answer immediately.
- Otherwise, use a priority queue of inter-component edges (both tree-tree and bone-tree) sorted by distance, merging components greedily (Kruskal-style) until some component accumulates k bones, then output the squared threshold.
