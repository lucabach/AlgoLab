# Real Estate Market

Given buyers, properties, and state-capacity constraints, find the maximum number of properties sold and the maximum total revenue under those constraints.

## Approach

- Model as a min-cost max-flow problem: source connects to each buyer (capacity 1, cost 0), each buyer connects to properties they bid on (capacity 1, cost = negated bid), and each property connects to its state node which drains to the sink with the state's capacity.
- Run successive shortest paths to find maximum flow at minimum cost; convert the negated costs back to revenue.
