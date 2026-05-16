# Return of the Jedi

Given a complete weighted graph, find the second minimum spanning tree cost.

## Approach

- Compute the MST using Kruskal's algorithm and record its total cost.
- For every non-MST edge (u, v), the cost of the alternative spanning tree obtained by swapping that edge in is: MST cost + weight(u,v) - max edge weight on the MST path from u to v.
- Precompute the max edge on every pair of MST paths via DFS, then take the minimum swap cost over all non-MST edges.
