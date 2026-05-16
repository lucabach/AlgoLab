# Clues

Given n radio stations with radius r, determine whether frequencies can be assigned so no two interfering stations share a frequency, and for each query pair (Holmes, Watson) whether they can communicate through the network.

## Approach

- Build a Delaunay triangulation of all stations, then BFS over Delaunay neighbors within distance r to 2-color the interference graph. If any same-color conflict is detected, the whole network has interference.
- Separate the stations into two color classes (red/black) and rebuild their own triangulations; check that neither class has internal interference.
- For each query, check direct communication (distance ≤ r), reachability to the network, and whether Holmes and Watson are in the same connected component.
