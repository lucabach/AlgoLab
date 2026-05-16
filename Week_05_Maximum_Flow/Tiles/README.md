# Tiles

Given a grid with some cells blocked, determine whether all non-blocked cells can be tiled with 1x2 dominoes (each covering two adjacent cells).

## Approach

Model non-blocked cells as graph vertices with edges between adjacent cells. A perfect tiling exists iff there is a perfect matching on the non-blocked cells. Use Edmonds' maximum cardinality matching; if the matching covers all non-blocked cells, output "yes".
