# Algocoon

Given a directed graph representing an Algocoon figure, find the minimum cut that separates the figure into two parts.

## Approach

- The minimum cut value is independent of which node is source or sink (in an undirected sense), so iterate over all consecutive node pairs (i, i+1 mod n) as source-sink pairs and run max-flow for each.
- The answer is the minimum over all those max-flow values.
