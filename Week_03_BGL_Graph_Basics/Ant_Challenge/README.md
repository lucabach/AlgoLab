# Ant Challenge

Given a graph with s species of ants, each species has its own edge weights and a home hive. Find the shortest path between two nodes a and b using only edges that belong to the MST of at least one species.

## Approach

For each species, compute its MST (Prim from the species' hive) and add the MST edges to a combined graph. Run Dijkstra on this combined graph from a to b. The combined graph contains only "approved" edges, so the shortest path over it is the answer.
