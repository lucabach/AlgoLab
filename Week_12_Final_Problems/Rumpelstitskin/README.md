# Rumpelstitskin

Given two separate flow networks (one for goblins, one for humans) connected through a set of shared nodes with scores, find the maximum flow and maximum score of paths that traverse both networks through the shared nodes.

## Approach

- Build a combined min-cost flow graph: the goblin network flows left-to-right, the human network flows right-to-left, and shared nodes are split (in/out) with an edge of capacity 1 carrying a negated score (plus an offset for non-negativity).
- Run successive shortest paths from the goblin source to the human source; recover the actual flow and total score from the cost.
