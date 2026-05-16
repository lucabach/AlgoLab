# Marathon

Given a weighted directed graph with a start and finish, find the maximum number of runners that can travel from start to finish along shortest paths simultaneously.

## Approach

- Run Dijkstra from the start and from the finish to find shortest-path distances from both ends.
- Remove any edge that is not on a shortest path (i.e., start_dist[u] + edge_cost + finish_dist[v] != shortest_total).
- Run max-flow on the pruned graph; the result is the number of runners that can travel simultaneously along shortest paths.
