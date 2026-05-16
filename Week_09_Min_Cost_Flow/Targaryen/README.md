# Targaryen

Given a city graph with barracks, plazas, and a distance limit, find the maximum number of soldier-civilian pairs that can be matched where soldiers start at barracks and civilians stand near reachable plazas.

## Approach

- Run Dijkstra from each barrack and mark all nodes reachable within distance d.
- Build a subgraph of reachable nodes; duplicate plaza nodes to allow soldiers to be matched to civilians at adjacent reachable positions.
- Run Edmonds' maximum cardinality matching on the resulting bipartite-like graph.
