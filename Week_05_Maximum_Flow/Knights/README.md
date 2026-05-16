# Knights

Place k knights on an m x n chessboard (with c knights allowed per cell) and find the maximum number that can escape to the board boundary, where each cell-to-cell connection has capacity 1.

## Approach

Model as max-flow with node splitting: each cell (i, j) has an IN and OUT node connected by an edge of capacity c. Adjacent cells connect OUT(i,j) -> IN(neighbor) with capacity 1. Boundary cells connect their OUT to the sink (with capacity equal to the number of exits). Source connects to each knight's starting cell IN node. Max-flow gives the number of knights that can escape.
