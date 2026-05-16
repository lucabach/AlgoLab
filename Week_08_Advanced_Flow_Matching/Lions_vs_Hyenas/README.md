# Lions vs Hyenas

Given a graph where nodes have affinities for either Simba or Nala and edges have friendship values, determine the minimum dissatisfaction (or maximum satisfaction) when splitting the group.

## Approach

- Model the problem as a minimum cut: build two directed flow graphs from Simba to Nala, encoding node affinities as capacities on edges connected to source/sink.
- Run max-flow (= min-cut) on both orientations and pick the smaller cut; with two lions the answer is the min-cut, with one it's the total minus twice the min-cut.
