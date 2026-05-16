# First Steps with BGL

Given a weighted undirected graph, output the total weight of its minimum spanning tree and the maximum shortest-path distance from vertex 0 to any other vertex.

## Approach

Run Kruskal's algorithm (BGL) to find the MST and sum edge weights. Run Dijkstra from vertex 0 and take the maximum distance in the result vector.
