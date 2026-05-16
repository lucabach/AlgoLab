# Fleetrace

Given b boats, s sailors, and p possible pairings with compatibility scores, find the assignment of sailors to boats that maximizes total score.

## Approach

- Model as min-cost max-flow: source connects to each boat (capacity 1), each boat connects to matched sailors via pairing edges (cost = negated score + offset), sailors connect to the sink (capacity 1), and each boat also has a dummy edge to the sink to allow unmatched boats.
- Run successive shortest paths and recover the maximum score from the flow cost.
