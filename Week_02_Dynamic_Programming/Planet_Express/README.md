# Planet Express

Given a directed graph with teleportation nodes, find the minimum-cost path from node n-1 to any of the first k nodes, where teleport nodes in the same strongly connected component can warp between each other cheaply.

## Approach

Reverse all edges and run from node n-1. Find SCCs; for each SCC containing more than one teleport node, add virtual hub edges (teleport node -> hub with cost = SCC size - 1, hub -> teleport node with cost 0) to model free inter-SCC teleportation. Run Dijkstra from n-1 and take the minimum distance to any of the first k nodes.
