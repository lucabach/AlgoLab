# Asterix the Gaul

Asterix must travel at least distance D in time less than T by making a sequence of moves (each with a distance and time cost) and optionally drinking magic potion gulps that add extra distance per move. Find the minimum number of potion gulps needed.

## Approach

Split moves into two halves and enumerate all subsets of each (meet-in-the-middle). For each subset pair whose combined time is under T, record the best distance achievable per number of moves. Binary search on the number of gulps: for each candidate gulp count, check if any number of moves can push the total distance to at least D using `best_distance[moves] + moves * gulp[gulps] >= D`.
