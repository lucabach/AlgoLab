# Important Bridges

Given an undirected graph, find all bridges (edges whose removal disconnects the graph) and output them sorted lexicographically.

## Approach

Use BGL's biconnected components algorithm. A biconnected component with exactly one edge is a bridge. Collect all such edges, normalize each as (min, max) for consistent ordering, sort, and output.
